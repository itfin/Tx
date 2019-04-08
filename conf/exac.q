\d .conf
ex.XSHG.session:(09:15 09:25;09:30 11:30;13:00 15:00);        /上交所
ex.XSHE.session:(09:15 09:25;09:30 11:30;13:00 15:00);        /深交所
ex.XHKG.session:(09:00 09:25;09:30 12:00;13:00 16:00);        /联交所 
ex.CCFX.session:(09:28 09:29;09:30 11:30;13:00 15:15);        /中金所
ex.XSGE.session:(00:00 02:30;08:58 08:59;09:00 10:15;10:30 11:30;13:30 15:00;20:58 20:59;21:00 24:00);        /上期所
ex.XDCE.session:(00:00 02:30;08:58 08:59;09:00 10:15;10:30 11:30;13:30 15:00;20:58 20:59;21:00 24:00);        /大商所
ex.XZCE.session:(08:58 08:59;09:00 10:15;10:30 11:30;13:30 15:00;20:58 20:59;21:00 23:30);          /郑商所
ex.XSES.session:(00:00 04:45;09:00 16:30;17:00 24:00);        /新加坡A50 
ex.FX.session:(00:00 05:00;05:15 24:00);                      /外汇
ex.METAL.session:(00:00 05:10;06:00 24:00);                   /现货贵金属

ac:()!();
ac[`]:`pxunit`qtylot`qtymax!1e-4 1e0 0w;
ac[`BShareSZ]:ac[`AShare]:`pxunit`qtylot`qtymax!1e-2 1e2 1e6;
ac[`BShareSS]:ac[`Warrant]:ac[`Fund]:`pxunit`qtylot`qtymax!1e-3 1e2 1e6;
ac[`RepoSZ]:ac[`BondSZ]:`pxunit`qtylot`qtymax!1e-3 10 1e5;
ac[`BondSS]:`pxunit`qtylot`qtymax!1e-3 1 1e4;
ac[`RepoSS]:`pxunit`qtylot`qtymax!5e-3 1e2 1e4;
ac[`Future]:`pxunit`qtylot`qtymax!1e-2 1e1 1e2;

jc.hk:`s#0.01 0.25 0.5 10 20 100 200 500 1000 2000 5000 9995!0.001 0.005 0.01 0.02 0.05 .1 .2 .5 1 2 5 0;
hkticks:`s#raze {x[0]+x[1]*til 1|`int$(x[2]-x[0])%x[1]} each flip (key;value;('[;]/)(fills;next;key))@\: jc.hk;

\d .