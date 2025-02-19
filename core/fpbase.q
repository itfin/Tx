.module.fpbase:2014.09.24;

//在两个不同节点的tp之间进行消息转发.应用场景为内网Tx模块和外网Tx模块通过代理模块的总线转发机制相互通信.tp为内网总线,tp2为外网总线,fp为转发代理,ft在内网,fe在外网，则通讯链路为ft<->tp<->fp<->tp2<->fe
//.conf.proxy.stp字典为消息源模块所在总线，代理模块收到的订阅消息根据源模块转发到对端tp

upd:{[t;x].temp.t:t;.temp.x:x;if[1b~.conf[`dumpapi];insert[t;update dsttime:.z.P from x]];src:x[0;`src];if[not src in key .conf.proxy.stp;:()];{[d;t;x]h:.ctrl.conn[d;`h];$[-6h<>type h;();0>=h;();[neg[h] (".u.upd";t;x)]];}[;t;value flip x] each .conf.proxy.tpl except .conf.proxy.stp src;};

//----ChangeLog----
//2024.09.24:upd增加对src配置存在的检查以避免误配置引发环回风暴
//2024.04.24:增加使用注释,upd函数增加对dumpapi支持
//2017.08.23:初始版本

