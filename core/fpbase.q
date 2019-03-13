.module.fpbase:2017.08.23;
//在两个不同节点的tp之间进行消息转发

upd:{[t;x]src:x[0;`src];{[d;t;x]h:.ctrl.conn[d;`h];$[-6h<>type h;();0>=h;();[neg[h] (".u.upd";t;x)]];}[;t;value flip x] each .conf.proxy.tpl except .conf.proxy.stp src;};



