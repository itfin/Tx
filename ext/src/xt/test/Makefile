#
# Net Library Makefile
#
#
export BUILD_HOME_DIR = $(shell pwd)
export BUILD_OUT_DIR  = $(BUILD_HOME_DIR)/lib/
export BUILD_INCS 	  =  -I/usr/local/include -I$(BUILD_HOME_DIR)/C++/ -I$(BUILD_HOME_DIR)/include/
export CXX = g++ -fPIC -Wall -O2 -DNDEBUG -DPV_DEPLOY -fno-strict-aliasing -fexec-charset=GBK 

PROGRAM = TestTraderApi
LIBS    = -L$(BUILD_OUT_DIR)
SOURCE  = $(wildcard ./*/*.cpp)
OBJS 	= $(patsubst %.cpp,%.o, $(SOURCE)) 

%.o: %.cpp
	$(CXX) -c $(BUILD_INCS) -o $@ $?

$(PROGRAM):$(OBJS)
	$(CXX) -o $(BUILD_OUT_DIR)/$@ $^ $(LIBS) -lXtTraderApi

clean:
	rm -f $(OBJS) $(BUILD_OUT_DIR)/$(PROGRAM)
