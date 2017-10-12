--#################################################################################################
--��   ��: StockInfoDB
--��   ��: �������ݿ�
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: ���ݿ����ƣ����ݿ��ļ�·���������Ҫ�޸ġ�
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
--��   ��:
--��������: ������Ʊ��Ϣ�б�.
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: TBL_StockDef������,TTD_StockDef�Ǹ���.�����������������ݵ�����.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_StockDef')
begin
    drop table TBL_StockDef
end
go

create table TBL_StockDef
(
StockCode             int             not null primary key, --����
StockName             nvarchar(16)    not null unique,  --����
Category              varchar(32)     null, --��ҵ
PERatio               real            null, --��ӯ��=ÿ���м�/ÿ��ӯ��
PBRatio               real            null, --�о���=ÿ�ɹɼ�/ÿ�ɾ��ʲ�
MktValue              money           null, --����ֵ
Circulation           money           null  --��ֵͨ
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
----�������ݵ�����[1].
truncate table TTD_StockDef

----�������ݵ�����[2].
----TTD,FMT��ʽ���ļ��Ѿ�����ϴ����ٶ�������(http://pan.baidu.com/s/1gdCNWQZ). 
bulk insert TTD_StockDef
from 'D:\TTD_StockDef.TTD'
with (formatfile='D:\TTD_StockDef.FMT');

----�Ѹ�������ͬ��������.
insert into TBL_StockDef(StockCode,StockName,Category,PERatio,PBRatio,MktValue,Circulation)
select t1.StockCode,t1.StockName,t1.Category,t1.PERatio,t1.PBRatio,t1.MktValue,t1.Circulation
from TTD_StockDef t1
left join TBL_StockDef t2 on t1.StockCode = t2.StockCode
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--��   ��:
--��������: ������Ȩ��Ϣ��Ϣ��
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: TBL_XRDHistory������,TTD_XRDHistory�Ǹ���.�����������������ݵ�����.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_XRDHistory')
begin
    drop table TBL_XRDHistory
end
go

create table TBL_XRDHistory
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --ʱ��
ExtendPics            real            not null, --�͹�
AllotPics             real            not null, --���
AllotmentPrice        real            not null, --��ɼ�
Bonus                 real            not null, --�ֺ�
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
----�������ݵ�����[1].
truncate table TTD_XRDHistory

----�������ݵ�����[2].
----TTD,FMT��ʽ���ļ��Ѿ�����ϴ����ٶ�������(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD��ʽ���ļ�������Ҫ�޸�Ϊ�����ϴ�ʱ�����ʵ���ļ�����.�м����ļ�,��һ����Ҫʵ�м���.
bulk insert TTD_XRDHistory
from 'D:\TTD_XRDHistory.TTD'
with (formatfile='D:\TTD_XRDHistory.FMT');

----�Ѹ�������ͬ��������.
insert into TBL_XRDHistory(StockCode,StockDate,ExtendPics,AllotPics,AllotmentPrice,Bonus)
select t1.StockCode,t1.StockDate,t1.ExtendPics,t1.AllotPics,t1.AllotmentPrice,t1.Bonus
from TTD_XRDHistory t1
left join TBL_XRDHistory t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--��   ��:
--��������: ����ÿ���������ݱ�
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: TBL_EverydayPrice������,TTD_EverydayPrice�Ǹ���.�����������������ݵ�����.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_EverydayPrice')
begin
    drop table TBL_EverydayPrice
end
go

create table TBL_EverydayPrice
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --����
BeginPrice            real            not null, --����
MinPrice              real            not null, --���
MaxPrice              real            not null, --���
EndPrice              real            not null, --����
TotalHands            int             not null, --����
TotalValue            money           not null, --�ܶ�
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
----�������ݵ�����[1].
truncate table TTD_EverydayPrice

----�������ݵ�����[2].
----TTD,FMT��ʽ���ļ��Ѿ�����ϴ����ٶ�������(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD��ʽ���ļ�������Ҫ�޸�Ϊ�����ϴ�ʱ�����ʵ���ļ�����.�м����ļ�,��һ����Ҫʵ�м���.
bulk insert TTD_EverydayPrice
from 'D:\TTD_EverydayPrice.TTD'
with (formatfile='D:\TTD_EverydayPrice.FMT');

----�Ѹ�������ͬ��������.
insert into TBL_EverydayPrice(StockCode,StockDate,BeginPrice,MaxPrice,MinPrice,EndPrice,TotalHands,TotalValue)
select t1.StockCode,t1.StockDate,t1.BeginPrice,t1.MaxPrice,t1.MinPrice,t1.EndPrice,t1.TotalHands,t1.TotalValue
from TTD_EverydayPrice t1
left join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--��   ��:
--��������: ����ÿ��������չ��Ϣ���ݱ�
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: TBL_EverydayPriceEx������,TTD_EverydayPriceEx�Ǹ���.�����������������ݵ�����.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_EverydayPriceEx')
begin
    drop table TBL_EverydayPriceEx
end
go

create table TBL_EverydayPriceEx
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --ʱ��
AvgPrice              real            null, --����
Growth                real            null, --�Ƿ�
DealCount             int             null, --�ɽ�����
InnerHands            int             null, --����
OutterHands           int             null, --����
TotalHands            int             null, --����
TotalValue            money           null, --�ܶ�
TurnoverRate          real            null, --������
Amplitude             real            null, --���
BSP                   real            null, --ί��
BSD                   int             null, --ί��
VolumeRatio           real            null, --����
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
----�������ݵ�����[1].
truncate table TTD_EverydayPriceEx

----�������ݵ�����[2].
----TTD,FMT��ʽ���ļ��Ѿ�����ϴ����ٶ�������(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD��ʽ���ļ�������Ҫ�޸�Ϊ�����ϴ�ʱ�����ʵ���ļ�����.�м����ļ�,��һ����Ҫʵ�м���.
bulk insert TTD_EverydayPriceEx
from 'D:\TTD_EverydayPriceEx_20150430~20150515.TTD'
with (formatfile='D:\TTD_EverydayPriceEx.FMT');

----�Ѹ�������ͬ��������.
insert into TBL_EverydayPriceEx(StockCode,StockDate,AvgPrice,Growth,DealCount,
    InnerHands,OutterHands,TotalHands,TotalValue,TurnoverRate,Amplitude,BSP,BSD,VolumeRatio)
select t1.StockCode,t1.StockDate,t1.AvgPrice,t1.Growth,t1.DealCount,
    t1.InnerHands,t1.OutterHands,t1.TotalHands,t1.TotalValue,t1.TurnoverRate,t1.Amplitude,t1.BSP,t1.BSD,t1.VolumeRatio
from TTD_EverydayPriceEx t1
left join TBL_EverydayPriceEx t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--��   ��:
--��������: ����5�������ݱ�
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: TBL_5MinPrice������,TTD_5MinPrice�Ǹ���.�����������������ݵ�����.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_5MinPrice')
begin
    drop table TBL_5MinPrice
end
go

create table TBL_5MinPrice
(
StockCode             int             not null,
StockDate             smalldatetime   not null, --ʱ��
BeginPrice            real            not null, --���̼�
MinPrice              real            not null, --��ͼ�
MaxPrice              real            not null, --��߼�
EndPrice              real            not null, --���̼�
TotalHands            int             not null, --�ɽ���
TotalValue            money           not null, --��(�ֲ�)
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
----�������ݵ�����[1].
truncate table TTD_5MinPrice

----�������ݵ�����[2].
----TTD,FMT��ʽ���ļ��Ѿ�����ϴ����ٶ�������(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD��ʽ���ļ�������Ҫ�޸�Ϊ�����ϴ�ʱ�����ʵ���ļ�����.�м����ļ�,��һ����Ҫʵ�м���.
bulk insert TTD_5MinPrice
from 'D:\TTD_5MinPrice.TTD'
with (formatfile='D:\TTD_5MinPrice.FMT');

----�Ѹ�������ͬ��������.
insert into TBL_5MinPrice(StockCode,StockDate,BeginPrice,MaxPrice,MinPrice,EndPrice,TotalHands,TotalValue)
select t1.StockCode,t1.StockDate,t1.BeginPrice,t1.MaxPrice,t1.MinPrice,t1.EndPrice,t1.TotalHands,t1.TotalValue
from TTD_5MinPrice t1
left join TBL_5MinPrice t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--��   ��:
--��������: �����ֱ����ݱ�
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: TBL_EveryDealPrice������,TTD_EveryDealPrice�Ǹ���.�����������������ݵ�����.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_EveryDealPrice')
begin
    drop table TBL_EveryDealPrice
end
go

create table TBL_EveryDealPrice
(
StockCode            int             not null,
StockDate            smalldatetime   not null, --��ȷ����
CurPrice             real            null, --�ּ�
CurHands             int             null, --����
Buy1Price            real            null, --��һ��
Buy1Amount           int             null, --��һ��
Buy2Price            real            null, --�����
Buy2Amount           int             null, --�����
Sell1Price           real            null, --��һ��
Sell1Amount          int             null, --��һ��
Sell2Price           real            null, --������
Sell2Amount          int             null, --������
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
----�������ݵ�����[1].
truncate table TTD_EveryDealPrice

----�������ݵ�����[2].
----TTD,FMT��ʽ���ļ��Ѿ�����ϴ����ٶ�������(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD��ʽ���ļ�������Ҫ�޸�Ϊ�����ϴ�ʱ�����ʵ���ļ�����.�м����ļ�,��һ����Ҫʵ�м���.
bulk insert TTD_EveryDealPrice
from 'D:\TTD_EveryDealPrice.TTD'
with (formatfile='D:\TTD_EveryDealPrice.FMT');

----�Ѹ�������ͬ��������.
insert into TBL_EveryDealPrice(StockCode,StockDate,CurPrice,CurHands,
   Buy1Price,Buy1Amount,Buy2Price,Buy2Amount,Sell1Price,Sell1Amount,Sell2Price,Sell2Amount)
select t1.StockCode,t1.StockDate,t1.CurPrice,t1.CurHands,
   t1.Buy1Price,t1.Buy1Amount,t1.Buy2Price,t1.Buy2Amount,t1.Sell1Price,t1.Sell1Amount,t1.Sell2Price,t1.Sell2Amount
from TTD_EveryDealPrice t1
left join TBL_EveryDealPrice t2 on t1.StockCode = t2.StockCode and t1.StockDate = t2.StockDate
where t2.StockCode is null
*/

--/////////////////////////////////////////////////////////////////////////////////////////////////
--��   ��:
--��������: �����������ݱ�
--��������: 2015-05-01
--��   ��:
--�޸ļ�¼:
--��   ע: TBL_FinaHistory������,TTD_FinaHistory�Ǹ���.�����������������ݵ�����.
--///////////////////////////////////////////////////////////////////////////////////////////////////
if exists (select name from sysobjects where name='TBL_FinaHistory')
begin
    drop table TBL_FinaHistory
end
go

create table TBL_FinaHistory
(
StockCode            int             not null, --����
ReleaseDate          smalldatetime   not null, --��������
ReportDate           smalldatetime   not null, --������
ListedDate           smalldatetime   not null, --��������
EPS                  real            null, --ÿ������
NPS                  real            null, --ÿ�ɾ��ʲ�
NPR                  real            null, --���ʲ�������
CPS                  real            null, --ÿ�ɾ�Ӫ�ֽ�
PAFPS                real            null, --ÿ�ɹ�����
USPS                 real            null, --ÿ��δ����
ONP                  real            null, --������ͬ��
OMI                  real            null, --��Ӫ����ͬ��
SGPR                 real            null, --����ë����
AANA                 real            null, --����ÿ�ɾ���
TA                   money           null, --���ʲ�
MA                   money           null, --�����ʲ�
FA                   money           null, --�̶��ʲ�
IA                   money           null, --�����ʲ�
MD                   money           null, --������ծ
LD                   money           null, --���ڸ�ծ
TD                   money           null, --�ܸ�ծ
MI                   money           null, --��Ӫ����
OP                   money           null, --Ӫҵ����
TP                   float           null, --�ܹɱ�
MP                   float           null, --�����۹ɺϼ�
AMS                  float           null,  --A��
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
----�������ݵ�����[1].
truncate table TTD_FinaHistory

----�������ݵ�����[2].
----TTD,FMT��ʽ���ļ��Ѿ�����ϴ����ٶ�������(http://pan.baidu.com/s/1gdCNWQZ). 
----TTD��ʽ���ļ�������Ҫ�޸�Ϊ�����ϴ�ʱ�����ʵ���ļ�����.�м����ļ�,��һ����Ҫʵ�м���.
bulk insert TTD_FinaHistory
from 'D:\TTD_FinaHistory.TTD'
with (formatfile='D:\TTD_FinaHistory.FMT');

----�Ѹ�������ͬ��������.
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
--�� ��: 
--�� ��: ��ɸѡ��Ʊ����
--��������: 2015-05-01
--�� ��:
--�޸ļ�¼:
--�� ע: 
--#################################################################################################

----ѡ��'��ӯ��'��ΧΪ[0, 120]�Ĺ�Ʊ
select * from TBL_StockDef where PERatio >= 0 and PERatio <= 120

----ѡ����[2015-05-01,2015-05-15]�г�Ȩ��Ϣ�Ĺ�Ʊ
select t1.StockCode, t1.StockName, t2.*
from TBL_StockDef t1
join TBL_XRDHistory t2 on t1.StockCode = t2.StockCode
where t2.StockDate >= '2015-05-01' and t2.StockDate <= '2015-05-01'

----ѡ��-05-15��һ��, '���̼�'��ΧΪ[5,45]�Ĺ�Ʊ
select t1.StockCode, t1.StockName, t2.*
from TBL_StockDef t1
join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode
where t2.StockDate = '2015-05-15' and t2.EndPrice >= 5 and t2.EndPrice <= 45

----ѡ��-05-15��һ��, 'ƽ����'>'�м��' �Ĺ�Ʊ
select t1.StockCode, t1.StockName, t2.*
from TBL_StockDef t1
join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode
where t2.StockDate = '2015-05-15' and t2.TotalValue/t2.TotalHands > (t2.MinPrice+t2.MaxPrice)/2

----ѡ��-05-15��һ��, '������'>5% ͬʱ'Amplitude'>5% �Ĺ�Ʊ
select t1.StockCode, t1.StockName, t2.TurnoverRate, t2.Amplitude
from TBL_StockDef t1
join TBL_EverydayPriceEx t2 on t1.StockCode = t2.StockCode
where t2.StockDate = '2015-05-15' and t2.TurnoverRate > 0.05 and t2.Amplitude > 0.05

----ѡ��-05-15��һ��, '���̼�'��'2015-01-01������߼�'�İٷֱ���͵�ǰ֧��Ʊ
select top 100 t1.StockCode, t1.StockName, t2.EndPrice/t3.MaxPrice
from TBL_StockDef t1
join TBL_EverydayPrice t2 on t1.StockCode = t2.StockCode
join(select StockCode, MAX(MaxPrice) as MaxPrice
     from TBL_EverydayPrice
     where StockDate >= '2015-01-01'
     group by StockCode) t3 on t2.StockCode = t3.StockCode
where t2.StockDate = '2015-05-15'
order by t1.StockCode, t2.EndPrice/t3.MaxPrice asc
