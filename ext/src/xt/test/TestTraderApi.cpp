#include <CallBack.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    /* @test1 命令行方式，所有参数都通过命令行配置 */
    /*if (argc < 6)
    {
        std::cout << "Usage: ./TestTraderApi serverIpPort<192.168.1.185:65300> userName passwd fundAccount orderTimes";
        return -1;
    }
    string serverIpPort(argv[1]);
    string userName(argv[2]);
    string password(argv[3]);
    string fundAccount(argv[4]);
    int orderTimes = atoi(argv[5]);*/

    /* @test2 直接把各个参数写死在程序里，不方便也不推荐 */
    string serverIpPort("172.30.3.11:65300");
    string userName("260100007286");
    string password("@a1234567");
    string fundAccount("260100007286");
    int orderTimes(1);

    /* @test3 通过配置文件读取配置 */
    // 自行实现

    // 服务器地址、用户名、密码、资金账号、下单次数<端口皆为65300>
    xti::Callback* pCallback = new Callback(serverIpPort, userName, password, fundAccount, orderTimes);
    pCallback->init();
    pCallback->join();

    delete pCallback;
    return 0;
}
