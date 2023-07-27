#ifndef __SharedMem_H
#define __IpcMem_H

#ifdef LINUX

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <map>
#include <iostream>
#include <errno.h>
#include <chrono>
// #include "CoreConcept.h"
#include "Types.h"
#include "TableImp.h"
#include "ScalarImp.h"
#include "DolphinDB.h"


#define META_SIZE       1024000
#define MIN_MEM_ROW_SIZE    1000000
#define SHM_KEY_HEADER_STR  "/"
#define IPC_DATA_BUF_SIZE        1024000000
#define IPC_SEM_FLAG    1      /*set semaphore shared by multiprocess when init*/
#define IPC_MAX_NAME_LEN    32
#define TABLE_META_BASE_LEN  (sizeof(int)*2 + IPC_MAX_NAME_LEN)
#define DATA_HEADER_BASE_LENGTH (sizeof(int)*5)

namespace dolphindb {
/* Define a structure that will be imposed on the shared
    memory object */
struct ColMeta {
    int        type_; // column type
    int        length_; // column length
    int        nameLen_; // column name length
    char       name_[IPC_MAX_NAME_LEN]; 
};

struct TableMeta{
    int        nameLen_;
    char       name_[IPC_MAX_NAME_LEN];
    int        colNum_;
    char       colMeta_[2];
};

/*
* header to describe table meta in the begging of shared mem
*/
struct MemTableHeader {
    sem_t      readSem_;            /* POSIX unnamed semaphore */
    sem_t      writeSem_;
    size_t     bufSize_;
    size_t     tableCnt_;       /* table meta count in header of shared memory */
    size_t     metaOffset_;     /* meta write offset */
    size_t     writeOffset_;    /* data write offset */
    size_t     readOffset_;     /* read offset */
    int        readPage_;       /* the data in shared memory is a bounded  buffer, 
                                   read_rage is current total read times which finished total buffer, is used with write_page*/
    int        writePage_;      /* the data in shared memory is a bounded  buffer, 
                                   write is current total write times which finished total buffer, is used with read_page*/
    char       meta_[META_SIZE];  /* meta buffer to save meta data in header of shared memory */
    char       data_[2];          /* Data being transferred */
};

/*
* header to describe what table data in shared table belong.
*/
struct DataHeader {
    int        length_;
    int        timestampSeconds_;
    int        timestampMicro_;
    int        rows_;
    int        tablenameLen_;
    char       tablename_[2];
};


class TableMetaData {
  public:
    TableMetaData(std::string name): name_(name) {}
    ~TableMetaData() {}

    void debugPrint() { 
        //
    }

  public:
    std::string name_;
    std::vector<std::string> colNames_;
    std::vector<DATA_TYPE> colTypes_;
    std::vector<int> colLength_;
};

class IpcMemUtil {
 public:
   static void getMicroSeconds(int& seconds, int& microSeconds) {
       auto tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
       seconds = tp.time_since_epoch().count() / 1000000;
       microSeconds = tp.time_since_epoch().count() % 1000000;
   }

   static int calculateMicroCost(int seconds, int microSeconds) {
       auto tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
       int secondsCost = tp.time_since_epoch().count() / 1000000 - seconds;
       int microCost = tp.time_since_epoch().count() % 1000000 - microSeconds;
       return secondsCost * 1000000 + microCost;
   }
};


/*
*class to access shared memory, including open，read，write, close, unlink functions etc.
*/
class SharedMemStream {
  public:

   /**
    * @brief Construct a new Shared Mem Stream object
    * 
    * @param create  true/false, 
    * true: try to open sharedmem and init meta, if shared mem not exist,then create one. 
    * false: try to open shared memory, if shared mem not exist,then throw a exception.
    * @param path  String, the key to point the same shared memory between multi processes.
    * @param size  max data size of shared memory. the actual size is max of 1G and the param.
    */
   SharedMemStream(bool create, std::string path, int64_t size):  create_(create), path_(path), size_(size){
      shmpHeader_ = NULL;
      shmFd_ = 0;
   }
   ~SharedMemStream() {
   }

  public:
    /**
     * @brief wait the write process notify by sem and read data from shared memory, return a table.
     * 
     * @return TableSP 
     */
    TableSP readData(TableSP& copy, const bool& overwrite, size_t& readRows, int& microCost);
    
    void closeShm() {
      close(shmFd_);
    }

    /* Unlink the shared memory object. Even if the peer process
        is still using the object, this is okay. The object will
        be removed only after all open references are closed. */
    void unlinkShm() {
      shm_unlink(path_.c_str());
    }



    size_t getBufSize() {
      return shmpHeader_->bufSize_;
    }

    /**
     * @brief parse table meta in shared memory to local memory as a cache.
     * 
     * @param print 
     */
    void parseTableMeta(bool print);

  private:

    /* Create shared memory object and set its size to the size
        of our structure. open failed when memory is opened by other process
        if flag is SET by O_EXCL*/
    bool openSharedMem(std::string& errMsg);

  public:
    std::map<std::string, TableMetaData> tableMeta_;
    void readSemPost() {
      if (!shmpHeader_) {
        std::string errMsg;
        if(!openSharedMem(errMsg)) {
          throw RuntimeException("shm init error, msg:" + errMsg);
        }
      }

      if (sem_post(&shmpHeader_->readSem_) == -1) {
        throw RuntimeException("sem post error!");
      }
    }
  private:
    struct MemTableHeader *shmpHeader_;
    bool create_;
    std::string path_;
    int64_t size_;
    int shmFd_;
};


class IPCInMemTable : public BasicTable {
  public:
    IPCInMemTable(bool create, std::string shmPath, std::string tableName, const vector<ConstantSP>& cols, const vector<string>& colNames, size_t bufSize);
    virtual ~IPCInMemTable();
  
    virtual TABLE_TYPE getTableType() const {return IPCTBL;}
    TableSP read(TableSP& copy, const bool& overwrite, size_t& readRows, int& timeout);
    
    void closeShm();
    void unlinkShm();
    int getMicroCost();
  
  private:
    std::shared_ptr<SharedMemStream> pShmStream_;
    std::string tablename_;
    int microCost_;
    bool create_;
};

} // namespace dolphindb
#endif

#endif