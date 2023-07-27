#ifndef _STREAMING_H_
#define _STREAMING_H_
#include <functional>
#include <string>
#include <vector>
#include "Concurrent.h"
#include "DolphinDB.h"
#include "Util.h"
#include "SharedMem.h"

#ifdef _MSC_VER
	#ifdef _DDBAPIDLL	
		#define EXPORT_DECL _declspec(dllexport)
	#else
		#define EXPORT_DECL __declspec(dllimport)
	#endif
#else
	#define EXPORT_DECL 
#endif
namespace dolphindb {

#define DLOG true?DLogger::GetMinLevel() : DLogger::Info

class EXPORT_DECL Message : public ConstantSP {
public:
	Message() {
	}
	Message(const ConstantSP &sp) : ConstantSP(sp) {
	}
	Message(const ConstantSP &sp, const string &symbol) : ConstantSP(sp), symbol_(symbol) {
	}
	Message(const Message &msg) : ConstantSP(msg), symbol_(msg.symbol_) {
	}
	~Message() {
		clear();
	}
	Message& operator =(const Message& msg) {
		ConstantSP::operator=(msg);
		symbol_ = msg.symbol_;
		return *this;
	}
	const string& getSymbol() { return symbol_; }
private:
	string symbol_;
};

//using Message = ConstantSP;
using MessageQueue = BlockingQueue<Message>;
using MessageQueueSP = SmartPointer<MessageQueue>;
using MessageHandler = std::function<void(Message)>;
using MessageBatchHandler = std::function<void(vector<Message>)>;
using IPCInMemoryTableReadHandler = std::function<void(ConstantSP)>;

#define DEFAULT_ACTION_NAME "cppStreamingAPI"

class StreamingClientImpl;
class EXPORT_DECL StreamDeserializer {
public:
	//symbol->[dbPath,tableName], dbPath can be empty for table in memory.
	StreamDeserializer(const unordered_map<string, pair<string, string>> &sym2tableName, DBConnection *pconn = nullptr);
	StreamDeserializer(const unordered_map<string, DictionarySP> &sym2schema);
	StreamDeserializer(const unordered_map<string, vector<DATA_TYPE>> &symbol2col);
	bool parseBlob(const ConstantSP &src, vector<VectorSP> &rows, vector<string> &symbols, ErrorCodeInfo &errorInfo);
private:
	void create(DBConnection &conn);
	void parseSchema(const unordered_map<string, DictionarySP> &sym2schema);
	unordered_map<string, pair<string, string>> sym2tableName_;
	unordered_map<string, vector<DATA_TYPE>> symbol2col_;
	Mutex mutex_;
	friend class StreamingClientImpl;
};
typedef SmartPointer<StreamDeserializer> StreamDeserializerSP;

class EXPORT_DECL StreamingClient {
public:
	//listeningPort > 0 : listen mode, wait for server connection
	//listeningPort = 0 : active mode, connect server by DBConnection socket
	explicit StreamingClient(int listeningPort);
    virtual ~StreamingClient();
	bool isExit();
	void exit();

protected:
    MessageQueueSP subscribeInternal(string host, int port, string tableName, string actionName = DEFAULT_ACTION_NAME,
                                     int64_t offset = -1, bool resubscribe = true, const VectorSP &filter = nullptr,
                                     bool msgAsTable = false, bool allowExists = false, int batchSize  = 1,
									 string userName="", string password="",
									 const StreamDeserializerSP &blobDeserializer = nullptr);
    void unsubscribeInternal(string host, int port, string tableName, string actionName = DEFAULT_ACTION_NAME);

protected:
    SmartPointer<StreamingClientImpl> impl_;
};

class EXPORT_DECL ThreadedClient : public StreamingClient {
public:
	//listeningPort > 0 : listen mode, wait for server connection
	//listeningPort = 0 : active mode, connect server by DBConnection socket
    explicit ThreadedClient(int listeningPort);
    ~ThreadedClient() override = default;
    ThreadSP subscribe(string host, int port, const MessageHandler &handler, string tableName,
                       string actionName = DEFAULT_ACTION_NAME, int64_t offset = -1, bool resub = true,
                       const VectorSP &filter = nullptr, bool msgAsTable = false, bool allowExists = false,
						string userName="", string password="",
					   const StreamDeserializerSP &blobDeserializer = nullptr);
    ThreadSP subscribe(string host, int port, const MessageBatchHandler &handler, string tableName,
                       string actionName = DEFAULT_ACTION_NAME, int64_t offset = -1, bool resub = true,
                       const VectorSP &filter = nullptr, bool allowExists = false, int batchSize = 1,
						double throttle = 1,bool msgAsTable = false,
						string userName = "", string password = "",
						const StreamDeserializerSP &blobDeserializer = nullptr);
	size_t getQueueDepth(const ThreadSP &thread);
    void unsubscribe(string host, int port, string tableName, string actionName = DEFAULT_ACTION_NAME);
};

class EXPORT_DECL ThreadPooledClient : public StreamingClient {
public:
	//listeningPort > 0 : listen mode, wait for server connection
	//listeningPort = 0 : active mode, connect server by DBConnection socket
    explicit ThreadPooledClient(int listeningPort, int threadCount);
    ~ThreadPooledClient() override = default;
    vector<ThreadSP> subscribe(string host, int port, const MessageHandler &handler, string tableName,
                               string actionName, int64_t offset = -1, bool resub = true,
                               const VectorSP &filter = nullptr, bool msgAsTable = false, bool allowExists = false,
								string userName = "", string password = "",
							   const StreamDeserializerSP &blobDeserializer = nullptr);
    void unsubscribe(string host, int port, string tableName, string actionName = DEFAULT_ACTION_NAME);
	size_t getQueueDepth(const ThreadSP &thread);

private:
    int threadCount_;
};

class EXPORT_DECL PollingClient : public StreamingClient {
public:
	//listeningPort > 0 : listen mode, wait for server connection
	//listeningPort = 0 : active mode, connect server by DBConnection socket
    explicit PollingClient(int listeningPort);
    ~PollingClient() override = default;
    MessageQueueSP subscribe(string host, int port, string tableName, string actionName = DEFAULT_ACTION_NAME,
                             int64_t offset = -1, bool resub = true, const VectorSP &filter = nullptr,
                             bool msgAsTable = false, bool allowExists = false,
							string userName="", string password="",
							 const StreamDeserializerSP &blobDeserializer = nullptr);
    void unsubscribe(string host, int port, string tableName, string actionName = DEFAULT_ACTION_NAME);
};

#ifdef LINUX

class EXPORT_DECL IPCInMemoryStreamClient {
public:
	IPCInMemoryStreamClient() = default;
	~IPCInMemoryStreamClient();
	ThreadSP subscribe(const string& tableName, const IPCInMemoryTableReadHandler& handler, TableSP outputTable = nullptr, bool overwrite = true);
	void unsubscribe(const string& tableName);
private:
	struct ThreadWrapper {
		ThreadSP thread;
		bool isExit;
	};
	unordered_map<string, ThreadWrapper> tableName2thread_; // tableName -> (thread, isExit)
	ThreadSP newHandleThread(const string& tableName, const IPCInMemoryTableReadHandler handler,
		SmartPointer<IPCInMemTable> memTable,
		TableSP outputTable, bool overwrite);
};

#endif//LINUX

}  // namespace dolphindb
#endif  // _STREAMING_H_