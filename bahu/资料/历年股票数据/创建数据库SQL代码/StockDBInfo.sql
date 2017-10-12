--#################################################################################################
--名   称: StockInfoDB
--描   述: 创建数据库
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: 数据库名称，数据库文件路径请根据需要修改。
--#################################################################################################
create database StockInfoDB
on
(NAME = 'StockInfoDB_MDF',
 FILENAME = 'D:\StockInfoDB.mdf',
 SIZE = 10240MB,
 MAXSIZE = 51200MB,
 FILEGROWTH = 1024MB)
log on
(NAME = 'StockInfoDB_LDF',
 FILENAME = 'D:\StockInfoDB.ldf',
 SIZE = 2048MB,
 MAXSIZE = 10240MB,
 FILEGROWTH = 512MB);
go

use StockInfoDB;
go

--/////////////////////////////////////////////////////////////////////////////////////////////////
--名   称:
--功能描述: 创建股票信息列表.
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: TBL_StockDef是主表,TTD_StockDef是副表.副表用于批导入数据到主表.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_StockDef')
begin
    drop table TBL_StockDef
end
go

create table TBL_StockDef
(
StockCode             int             not null primary key, --代码
StockName             nvarchar(16)    not null unique,  --名称
Category              varchar(32)     null, --行业
PERatio               real            null, --市盈率=每股市价/每股盈利
PBRatio               real            null, --市净率=每股股价/每股净资产
MktValue              money           null, --总市值
Circulation           money           null  --流通值
);
go

if exists (select name from sysobjects where name='TTD_StockDef')
begin
    drop table TTD_StockDef
end
go

create table TTD_StockDef
(
StockCode             int             not null primary key,
StockName             nvarchar(16)    not null unique,
Category              varchar(32)     null,
PERatio               real            null,
PBRatio               real            null,
MktValue              money           null,
Circulation           money           null
);
go

/*
----导入数据到副表[1].
truncate table TTD_StockDef

----导入数据到副表[2].
----TTD,FMT格式的文件已经打包上传到百度网盘了(http://pan.baidu.com/s/1gdCNWQZ). 
bulk insert TTD_StockDef
from 'D:\TTD_StockDef.TTD'
with (formatfile='D:\TTD_StockDef.FMT');

----把副表数据同步到主表.
insert into TBL_StockDef(StockCode,StockName,Category,PERatio,PBRatio,MktValue,Circulation)
select t1.StockCode,t1.StockName,t1.Category,t1.PERatio,t1.PBRatio,t1.MktValue,t1.Circulation
from TTD_StockDef t1
left join TBL_StockDef t2 on t1.StockCode = t2.StockCode
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--名   称:
--功能描述: 创建除权除息信息表
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: TBL_XRDHistory是主表,TTD_XRDHistory是副表.副表用于批导入数据到主表.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_XRDHistory')
begin
    drop table TBL_XRDHistory
end
go

create table TBL_XRDHistory
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --时间
ExtendPics            real            not null, --送股
AllotPics             real            not null, --配股
AllotmentPrice        real            not null, --配股价
Bonus                 real            not null, --分红
primary key(StockCode, StockDate),
foreign key(StockCode) references TBL_StockDef(StockCode)
);
go

if exists (select name from sysobjects where name='TTD_XRDHistory')
begin
    drop table TTD_XRDHistory
end
go

create table TTD_XRDHistory
(
StockCode             int             not null,
StockDate             smalldatetime   not null,
ExtendPics            real            not null,
AllotPics             real            not null,
AllotmentPrice        real            not null,
Bonus                 real            not null
);
go

/*
----导入数据到副表[1].
truncate table TTD_XRDHistory

----导入数据到副表[2].
----TTD,FMT格式的文件已经打包上传到百度网盘了(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD格式的文件名称需要修改为网盘上带时间戳的实际文件名称.有几个文件,这一步就要实行几次.
bulk insert TTD_XRDHistory
from 'D:\TTD_XRDHistory.TTD'
with (formatfile='D:\TTD_XRDHistory.FMT');

----把副表数据同步到主表.
insert into TBL_XRDHistory(StockCode,StockDate,ExtendPics,AllotPics,AllotmentPrice,Bonus)
select t1.StockCode,t1.StockDate,t1.ExtendPics,t1.AllotPics,t1.AllotmentPrice,t1.Bonus
from TTD_XRDHistory t1
left join TBL_XRDHistory t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--名   称:
--功能描述: 创建每日行情数据表
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: TBL_EverydayPrice是主表,TTD_EverydayPrice是副表.副表用于批导入数据到主表.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_EverydayPrice')
begin
    drop table TBL_EverydayPrice
end
go

create table TBL_EverydayPrice
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --日期
BeginPrice            real            not null, --开盘
MinPrice              real            not null, --最低
MaxPrice              real            not null, --最高
EndPrice              real            not null, --收盘
TotalHands            int             not null, --总手
TotalValue            money           not null, --总额
primary key(StockCode, StockDate),
foreign key(StockCode) references TBL_StockDef(StockCode)
);
go

if exists (select name from sysobjects where name='TTD_EverydayPrice')
begin
    drop table TTD_EverydayPrice
end
go

create table TTD_EverydayPrice
(
StockCode             int             not null,
StockDate             smalldatetime   not null,
BeginPrice            real            not null,
MinPrice              real            not null,
MaxPrice              real            not null,
EndPrice              real            not null,
TotalHands            int             not null,
TotalValue            money           not null
);
go

/*
----导入数据到副表[1].
truncate table TTD_EverydayPrice

----导入数据到副表[2].
----TTD,FMT格式的文件已经打包上传到百度网盘了(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD格式的文件名称需要修改为网盘上带时间戳的实际文件名称.有几个文件,这一步就要实行几次.
bulk insert TTD_EverydayPrice
from 'D:\TTD_EverydayPrice.TTD'
with (formatfile='D:\TTD_EverydayPrice.FMT');

----把副表数据同步到主表.
insert into TBL_EverydayPrice(StockCode,StockDate,BeginPrice,MaxPrice,MinPrice,EndPrice,TotalHands,TotalValue)
select t1.StockCode,t1.StockDate,t1.BeginPrice,t1.MaxPrice,t1.MinPrice,t1.EndPrice,t1.TotalHands,t1.TotalValue
from TTD_EverydayPrice t1
left join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--名   称:
--功能描述: 创建每日行情扩展信息数据表
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: TBL_EverydayPriceEx是主表,TTD_EverydayPriceEx是副表.副表用于批导入数据到主表.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_EverydayPriceEx')
begin
    drop table TBL_EverydayPriceEx
end
go

create table TBL_EverydayPriceEx
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --时间
AvgPrice              real            null, --均价
Growth                real            null, --涨幅
DealCount             int             null, --成交笔数
InnerHands            int             null, --内盘
OutterHands           int             null, --外盘
TotalHands            int             null, --总手
TotalValue            money           null, --总额
TurnoverRate          real            null, --换手率
Amplitude             real            null, --振幅
BSP                   real            null, --委比
BSD                   int             null, --委差
VolumeRatio           real            null, --量比
primary key(StockCode, StockDate),
foreign key(StockCode) references TBL_StockDef(StockCode)
);
go

if exists (select name from sysobjects where name='TTD_EverydayPriceEx')
begin
    drop table TTD_EverydayPriceEx
end
go

create table TTD_EverydayPriceEx
(
StockCode             int             not null,
StockDate             smalldatetime   not null,
AvgPrice              real            null,
Growth                real            null,
DealCount             int             null,
InnerHands            int             null,
OutterHands           int             null,
TotalHands            int             null,
TotalValue            money           null,
TurnoverRate          real            null,
Amplitude             real            null,
BSP                   real            null,
BSD                   int             null,
VolumeRatio           real            null
);
go

/*
----导入数据到副表[1].
truncate table TTD_EverydayPriceEx

----导入数据到副表[2].
----TTD,FMT格式的文件已经打包上传到百度网盘了(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD格式的文件名称需要修改为网盘上带时间戳的实际文件名称.有几个文件,这一步就要实行几次.
bulk insert TTD_EverydayPriceEx
from 'D:\TTD_EverydayPriceEx_20150430~20150515.TTD'
with (formatfile='D:\TTD_EverydayPriceEx.FMT');

----把副表数据同步到主表.
insert into TBL_EverydayPriceEx(StockCode,StockDate,AvgPrice,Growth,DealCount,
    InnerHands,OutterHands,TotalHands,TotalValue,TurnoverRate,Amplitude,BSP,BSD,VolumeRatio)
select t1.StockCode,t1.StockDate,t1.AvgPrice,t1.Growth,t1.DealCount,
    t1.InnerHands,t1.OutterHands,t1.TotalHands,t1.TotalValue,t1.TurnoverRate,t1.Amplitude,t1.BSP,t1.BSD,t1.VolumeRatio
from TTD_EverydayPriceEx t1
left join TBL_EverydayPriceEx t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--名   称:
--功能描述: 创建5分钟数据表
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: TBL_5MinPrice是主表,TTD_5MinPrice是副表.副表用于批导入数据到主表.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_5MinPrice')
begin
    drop table TBL_5MinPrice
end
go

create table TBL_5MinPrice
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --时间
BeginPrice            real            not null, --开盘价
MinPrice              real            not null, --最低价
MaxPrice              real            not null, --最高价
EndPrice              real            not null, --收盘价
TotalHands            int             not null, --成交量
TotalValue            money           not null, --额(持仓)
primary key(StockCode, StockDate),
foreign key(StockCode) references TBL_StockDef(StockCode)
);
go

if exists (select name from sysobjects where name='TTD_5MinPrice')
begin
    drop table TTD_5MinPrice
end
go

create table TTD_5MinPrice
(
StockCode             int             not null,
StockDate             smalldatetime   not null,
BeginPrice            real            not null,
MinPrice              real            not null,
MaxPrice              real            not null,
EndPrice              real            not null,
TotalHands            int             not null,
TotalValue            money           not null
);
go

/*
----导入数据到副表[1].
truncate table TTD_5MinPrice

----导入数据到副表[2].
----TTD,FMT格式的文件已经打包上传到百度网盘了(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD格式的文件名称需要修改为网盘上带时间戳的实际文件名称.有几个文件,这一步就要实行几次.
bulk insert TTD_5MinPrice
from 'D:\TTD_5MinPrice.TTD'
with (formatfile='D:\TTD_5MinPrice.FMT');

----把副表数据同步到主表.
insert into TBL_5MinPrice(StockCode,StockDate,BeginPrice,MaxPrice,MinPrice,EndPrice,TotalHands,TotalValue)
select t1.StockCode,t1.StockDate,t1.BeginPrice,t1.MaxPrice,t1.MinPrice,t1.EndPrice,t1.TotalHands,t1.TotalValue
from TTD_5MinPrice t1
left join TBL_5MinPrice t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--名   称:
--功能描述: 创建分笔数据表
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: TBL_EveryDealPrice是主表,TTD_EveryDealPrice是副表.副表用于批导入数据到主表.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_EveryDealPrice')
begin
    drop table TBL_EveryDealPrice
end
go

create table TBL_EveryDealPrice
(
StockCode            int             not null,
StockDate            smalldatetime   not null, --精确到秒
CurPrice             real            null, --现价
CurHands             int             null, --现手
Buy1Price            real            null, --买一价
Buy1Amount           int             null, --买一量
Buy2Price            real            null, --买二价
Buy2Amount           int             null, --买二量
Sell1Price           real            null, --卖一价
Sell1Amount          int             null, --卖一量
Sell2Price           real            null, --卖二价
Sell2Amount          int             null, --卖二量
foreign key(StockCode) references TBL_StockDef(StockCode)
);
go

if exists (select name from sysobjects where name='IDX_EveryDealPrice')
begin
    drop index TBL_EveryDealPrice.IDX_EveryDealPrice
end
go

create index IDX_EveryDealPrice on TBL_EveryDealPrice(StockCode, StockDate)
go

if exists (select name from sysobjects where name='TTD_EveryDealPrice')
begin
    drop table TTD_EveryDealPrice
end
go

create table TTD_EveryDealPrice
(
StockCode            int             not null,
StockDate            smalldatetime   not null,
CurPrice             real            null,
CurHands             int             null,
Buy1Price            real            null,
Buy1Amount           int             null,
Buy2Price            real            null,
Buy2Amount           int             null,
Sell1Price           real            null,
Sell1Amount          int             null,
Sell2Price           real            null,
Sell2Amount          int             null
);
go

/*
----导入数据到副表[1].
truncate table TTD_EveryDealPrice

----导入数据到副表[2].
----TTD,FMT格式的文件已经打包上传到百度网盘了(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD格式的文件名称需要修改为网盘上带时间戳的实际文件名称.有几个文件,这一步就要实行几次.
bulk insert TTD_EveryDealPrice
from 'D:\TTD_EveryDealPrice.TTD'
with (formatfile='D:\TTD_EveryDealPrice.FMT');

----把副表数据同步到主表.
insert into TBL_EveryDealPrice(StockCode,StockDate,CurPrice,CurHands,
   Buy1Price,Buy1Amount,Buy2Price,Buy2Amount,Sell1Price,Sell1Amount,Sell2Price,Sell2Amount)
select t1.StockCode,t1.StockDate,t1.CurPrice,t1.CurHands,
   t1.Buy1Price,t1.Buy1Amount,t1.Buy2Price,t1.Buy2Amount,t1.Sell1Price,t1.Sell1Amount,t1.Sell2Price,t1.Sell2Amount
from TTD_EveryDealPrice t1
left join TBL_EveryDealPrice t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--名   称:
--功能描述: 创建财务数据表
--创建日期: 2015-05-01
--作   者:
--修改记录:
--备   注: TBL_FinaHistory是主表,TTD_FinaHistory是副表.副表用于批导入数据到主表.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_FinaHistory')
begin
    drop table TBL_FinaHistory
end
go

create table TBL_FinaHistory
(
StockCode            int             not null, --代码
ReleaseDate          smalldatetime   not null, --发布日期
ReportDate           smalldatetime   not null, --报告期
ListedDate           smalldatetime   not null, --上市日期
EPS                  real            null, --每股收益
NPS                  real            null, --每股净资产
NPR                  real            null, --净资产收益率
CPS                  real            null, --每股经营现金
PAFPS                real            null, --每股公积金
USPS                 real            null, --每股未分配
ONP                  real            null, --净利润同比
OMI                  real            null, --主营收入同比
SGPR                 real            null, --销售毛利率
AANA                 real            null, --调整每股净资
TA                   money           null, --总资产
MA                   money           null, --流动资产
FA                   money           null, --固定资产
IA                   money           null, --无形资产
MD                   money           null, --流动负债
LD                   money           null, --长期负债
TD                   money           null, --总负债
MI                   money           null, --主营收入
OP                   money           null, --营业利润
TP                   float           null, --总股本
MP                   float           null, --无限售股合计
AMS                  float           null,  --A股
primary key(StockCode, ReleaseDate),
foreign key(StockCode) references TBL_StockDef(StockCode)
);
go

if exists (select name from sysobjects where name='TTD_FinaHistory')
begin
    drop table TTD_FinaHistory
end
go

create table TTD_FinaHistory
(
StockCode            int             not null,
ReleaseDate          smalldatetime   not null,
ReportDate           smalldatetime   not null,
ListedDate           smalldatetime   not null,
EPS                  real            null,
NPS                  real            null,
NPR                  real            null,
CPS                  real            null,
PAFPS                real            null,
USPS                 real            null,
ONP                  real            null,
OMI                  real            null,
SGPR                 real            null,
AANA                 real            null,
TA                   money           null,
MA                   money           null,
FA                   money           null,
IA                   money           null,
MD                   money           null,
LD                   money           null,
TD                   money           null,
MI                   money           null,
OP                   money           null,
TP                   float           null,
MP                   float           null,
AMS                  float           null
);
go

/*
----导入数据到副表[1].
truncate table TTD_FinaHistory

----导入数据到副表[2].
----TTD,FMT格式的文件已经打包上传到百度网盘了(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD格式的文件名称需要修改为网盘上带时间戳的实际文件名称.有几个文件,这一步就要实行几次.
bulk insert TTD_FinaHistory
from 'D:\TTD_FinaHistory.TTD'
with (formatfile='D:\TTD_FinaHistory.FMT');

----把副表数据同步到主表.
insert into TBL_FinaHistory(StockCode,ReleaseDate,ReportDate,ListedDate, 
    EPS,NPS,NPR,CPS,PAFPS,USPS,ONP,OMI,SGPR,AANA,TA,MA,FA,IA,MD,LD,TD,MI,OP,TP,MP,AMS)
select t1.StockCode,t1.ReleaseDate,t1.ReportDate,t1.ListedDate, 
    t1.EPS,t1.NPS,t1.NPR,t1.CPS,t1.PAFPS,t1.USPS,t1.ONP,t1.OMI,t1.SGPR,
    t1.AANA,t1.TA,t1.MA,t1.FA,t1.IA,t1.MD,t1.LD,t1.TD,t1.MI,t1.OP,t1.TP,t1.MP,t1.AMS
from TTD_FinaHistory t1
left join TBL_FinaHistory t2 on t1.StockCode = t2.StockCode and t1.ReleaseDate = t2.ReleaseDate
where t2.StockCode is null
*/

--#################################################################################################
--名 称: 
--描 述: 批筛选股票范例
--创建日期: 2015-05-01
--作 者:
--修改记录:
--备 注: 
--#################################################################################################

----选出'市盈率'范围为[0, 120]的股票
select * from TBL_StockDef where PERatio >= 0 and PERatio <= 120

----选出在[2015-05-01,2015-05-15]有除权除息的股票
select t1.StockCode, t1.StockName, t2.*
from TBL_StockDef t1
join TBL_XRDHistory t2 on t1.StockCode = t2.StockCode
where t2.StockDate >= '2015-05-01' and t2.StockDate <= '2015-05-01'

----选出-05-15这一天, '收盘价'范围为[5,45]的股票
select t1.StockCode, t1.StockName, t2.*
from TBL_StockDef t1
join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode
where t2.StockDate = '2015-05-15' and t2.EndPrice >= 5 and t2.EndPrice <= 45

----选出-05-15这一天, '平均价'>'中间价' 的股票
select t1.StockCode, t1.StockName, t2.*
from TBL_StockDef t1
join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode
where t2.StockDate = '2015-05-15' and t2.TotalValue/t2.TotalHands > (t2.MinPrice+t2.MaxPrice)/2

----选出-05-15这一天, '换手率'>5% 同时'Amplitude'>5% 的股票
select t1.StockCode, t1.StockName, t2.TurnoverRate, t2.Amplitude
from TBL_StockDef t1
join TBL_EverydayPriceEx t2 on t1.StockCode = t2.StockCode
where t2.StockDate = '2015-05-15' and t2.TurnoverRate > 0.05 and t2.Amplitude > 0.05

----选出-05-15这一天, '收盘价'与'2015-01-01以来最高价'的百分比最低的前支股票
select top 100 t1.StockCode, t1.StockName, t2.EndPrice/t3.MaxPrice
from TBL_StockDef t1
join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode
join(select StockCode, MAX(MaxPrice) as MaxPrice
     from TBL_EverydayPrice
     where StockDate >= '2015-01-01'
     group by StockCode) t3 on t2.StockCode = t3.StockCode
where t2.StockDate = '2015-05-15'
order by t1.StockCode, t2.EndPrice/t3.MaxPrice asc
