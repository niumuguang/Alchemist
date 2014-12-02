-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE DEFINER=`root`@`localhost` PROCEDURE `insert5Min_ag1506`(

in InstrumentID varchar(10),
in TradingDay date,
/*
in UpdateTime time,
*/
in LastPrice float,
in AskPrice1 float,
in BidPrice1 float,
in AskVolume1  int(11),
in BidVolume1  int(11),
in AveragePrice float,
in ClosePrice float,
in CurrDelta float,
in ExchangeID varchar(45),
in HighestPrice float,
in LowestPrice float,
in UpperLimitPrice float,
in LowerLimitPrice float,
in Openinterest  int(11),
in OpenPrice float,
in PreClosePrice float,
in PreOpeninterest  int(11),
in PreSettlementPrice float,
in Volume int(11)

)
BEGIN

#输入变量本地化声明
DECLARE mInstrumentID varchar(10);
DECLARE mTradingDay date;
DECLARE mUpdateTime time;
DECLARE mLastPrice float;
DECLARE mAskPrice1 float;
DECLARE mBidPrice1 float;
DECLARE mAskVolume1  int(11);
DECLARE mBidVolume1  int(11);
DECLARE mAveragePrice float;
DECLARE mClosePrice float;
DECLARE mCurrDelta float;
DECLARE mExchangeID varchar(45);
DECLARE mHighestPrice float;
DECLARE mLowestPrice float;
DECLARE mUpperLimitPrice float;
DECLARE mLowerLimitPrice float;
DECLARE mOpeninterest  int(11);
DECLARE mOpenPrice float;
DECLARE mPreClosePrice float;
DECLARE mPreOpeninterest  int(11);
DECLARE mPreSettlementPrice float;
DECLARE mVolume int(11);
#计算过程中的临时变量声明
DECLARE MinTableCount int default 0;			#分钟表的个数
Declare MinCompare1 int default 0;			#分钟数比较时使用的变量
Declare MinCompare2 int default 0;			
Declare MinCompare3 int default 0;
Declare MinCompareTmp int default 0;
Declare HourCompare1 int default 0;			#小时数比较时使用的变量
Declare HourCompare2 int default 0;			
Declare HourCompare3 int default 0;

DECLARE CompareTempTime time;
DECLARE CompareTempDate date;
DECLARE CompareTempDateTime1 datetime;
DECLARE CompareTempDateTime2 datetime;
declare CompareTempInt int default 0;

Declare tmpMinuteNum int default 0;			#分钟数
Declare tmpSubDataNum int default 0;			#先存储的tick数据数量
DECLARE tmpAveragePrice float default 0;		
DECLARE tmpHighestPrice float default 0;
DECLARE tmpLowestPrice float default 0;
DECLARE tmpVolume int default 0;
DECLARE tmpStartVolume int default 0;
DECLARE tmpOpenInterest int default 0;
DECLARE tmpAskPrice1 float default 0;
DECLARE tmpBidPrice1 float default 0;
DECLARE tmpAskVolume1 int default 0;
DECLARE tmpBidVolume1 int default 0;
DECLARE tmpNum	int default 0; #临时使用整形数据
DECLARE MinConst int default 5;
#####################################################################################################
#变量初始化
SET mInstrumentID = InstrumentID;
SET mTradingDay = TradingDay;
#SET mUpdateTime = UpdateTime;
SET mUpdateTime = curtime();
SET mLastPrice = LastPrice;
SET mAskPrice1 = AskPrice1;
SET mBidPrice1 = BidPrice1;
SET mAskVolume1 = AskVolume1;
SET mBidVolume1 = BidVolume1;
SET mAveragePrice = AveragePrice;
SET mClosePrice = ClosePrice;
SET mCurrDelta = CurrDelta;
SET mExchangeID = ExchangeID;
SET mHighestPrice = HighestPrice;
SET mLowestPrice = LowestPrice;
SET mUpperLimitPrice = UpperLimitPrice;
SET mLowerLimitPrice = LowerLimitPrice;
SET mOpeninterest = Openinterest;
SET mOpenPrice = OpenPrice;
SET mPreClosePrice = PreClosePrice;
SET mPreOpeninterest = PreOpeninterest;
SET mPreSettlementPrice = PreSettlementPrice;
SET mVolume = Volume;
set MinConst = 5;

-- ------------------------------------------------------------------------------------
#如果插入的 分钟表数量为零则直接插入第一个值
#分钟表根据需要进行修改
SELECT count(id) into MinTableCount  FROM IronDB.ag1506_5Min;
select minute(mUpdateTime) into MinCompareTmp;
if (MinTableCount = 0) && (MOD(MinCompareTmp, MinConst)=0 ) && (mAskPrice1 != 0) then
	insert into IronDB.ag1506_5Min(
	InstrumentID,
	TradingDay,
	UpdateTime,
	MinuteNum,
	LastPrice,
	AskPrice1,
	BidPrice1,
	AskVolume1,
	BidVolume1,
	AveragePrice,
	ClosePrice,
	CurrDelta,
	ExchangeID,
	HighestPrice,
	LowestPrice,
	UpperLimitPrice,
	LowerLimitPrice,
	OpenInterest,
	OpenPrice,
	PreClosePrice,
	PreOpenInterest,
	PreSettlementPrice,
	StartVolume,
	EndVolume,
	Volume,
	SubDataNum
	) value(
	mInstrumentID,
	mTradingDay,
	mUpdateTime,
	Minute(mUpdateTime),			#开始分钟数为零select Minute(mUpdateTime) into MinCompare2;
	mLastPrice,
	mAskPrice1,
	mBidPrice1,
	mAskVolume1,
	mBidVolume1,
	mLastPrice,		#均价就是最新价
	mLastPrice,		#最新价就是收盘价
	mCurrDelta,
	mExchangeID,
	mLastPrice,		#最高价也是最新价
	mLastPrice,		#最低价也是最新价
	mUpperLimitPrice,
	mLowerLimitPrice,
	mOpeninterest,
	mLastPrice,		#开盘价格为当前价格
	mPreClosePrice,
	mPreOpeninterest,
	mPreSettlementPrice,
	mVolume,				#第一次为0 每次更新时为 openinterest - old openinterest + 当强vol
	mVolume,
	'0',
	'1'
	);
end if;

######################################################################
#如果插入的 分钟表的分钟数与插入值相同时 更新最有一条数据
#分钟表根据需要进行修改ag1506_5Min  HourCompare1
select MinuteNum into MinCompare1 from IronDB.ag1506_5Min order by id desc limit 0,1;

select UpdateTime into CompareTempTime from IronDB.ag1506_5Min order by id desc limit 0,1;
select TradingDay into CompareTempDate from IronDB.ag1506_5Min order by id desc limit 0,1;

#select UpdateTime into @ff from IronDB.ag1506_5Min order by id desc limit 0,1;


select UpdateTime into @ss from IronDB.ag1506_5Min order by id desc limit 0,1;
insert into IronDB.TestTable(TestTime)value(@ss);

#insert into IronDB.TestTable(TestTime)value( select UpdateTime from IronDB.ag1506_5Min order by id desc limit 0,1 );


select date_format(CompareTempDate,'%Y-%c-%d') into @str1;
select time_format(CompareTempTime,' %H:%i:%S') into @str2;
select CONCAT(@str1,@str2) into @str3;
select STR_TO_DATE(@str3, '%Y-%m-%d %H:%i:%S') into CompareTempDateTime1;

select date_format(mTradingDay,'%Y-%c-%d') into @str4;
select time_format(mUpdateTime,' %H:%i:%S') into @str5;
select CONCAT(@str4,@str5) into @str6;
select STR_TO_DATE(@str6, '%Y-%m-%d %H:%i:%S') into CompareTempDateTime2;


#SELECT MySQLTimeStamp into CompareTempDateTime2 from IronDB.ag1506_5Min order by id desc limit 0,1;
set @res = ABS( TIMESTAMPDIFF(MINUTE, CompareTempDateTime1, CompareTempDateTime2) );
set CompareTempInt = @res;
#insert into IronDB.TestTable(TestTimeStamp,TestTimeStamp2,TestInt,TestTime,TestDate)
#value(CompareTempDateTime1,CompareTempDateTime2,@res,CompareTempTime,CompareTempDate);

#if (MinCompare2-MinCompare1)<MinConst then
if (@res<MinConst)&&(mAskPrice1 != 0 ) then
	#先从最后一行获取需要的数据
	#分钟表根据需要进行修改
	SELECT SubDataNum into tmpSubDataNum FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT AveragePrice into tmpAveragePrice FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT HighestPrice into tmpHighestPrice FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT LowestPrice into tmpLowestPrice FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT StartVolume into tmpStartVolume FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT OpenInterest into tmpOpenInterest FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT AskPrice1 into tmpAskPrice1 FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT BidPrice1 into tmpBidPrice1 FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT AskVolume1 into tmpAskVolume1 FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	SELECT BidVolume1 into tmpBidVolume1 FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	#SELECT MinuteNum,SubDataNum into tmpMinuteNum,tmpSubDataNum FROM IronDB.ag1506_5Min ORDER BY id DESC LIMIT 1;
	#tmpAskVolume1
	#计算需要计算的数据
	set tmpNum = tmpSubDataNum+1;
	#tmpAveragePrice 获取的均价为价格的100倍关系 todo 所以需要修改
	set tmpAveragePrice = (tmpAveragePrice*tmpSubDataNum + mLastPrice)/tmpNum;
	set tmpAskPrice1 = (tmpAskPrice1*tmpSubDataNum + mAskPrice1)/tmpNum;
	set tmpBidPrice1 = (tmpBidPrice1*tmpSubDataNum + mBidPrice1)/tmpNum;
	set tmpAskVolume1 = (tmpAskVolume1*tmpSubDataNum + mAskVolume1)/tmpNum;
	set tmpBidVolume1 = (tmpBidVolume1*tmpSubDataNum + mBidVolume1)/tmpNum;

	#再设置进去计算好的数据结果
	#if mAskPrice1 != 0 then
		UPDATE IronDB.ag1506_5Min 
		set #MinuteNum = MinCompare3,
		LastPrice = mLastPrice, 
		#UpdateTime = mUpdateTime,
		HighestPrice = mLastPrice,
		LowestPrice = mLastPrice,
		SubDataNum = tmpNum,				
		Volume = (mVolume - tmpStartVolume),#放在均价后更新 todo开盘价要改的
		EndVolume = mVolume,
		ClosePrice = mLastPrice,
		OpenInterest = tmpOpenInterest,
		AveragePrice = mLastPrice,
		AskPrice1 = tmpAskPrice1,AskVolume1 = tmpAskVolume1,
		BidPrice1 = tmpBidPrice1,BidVolume1 = tmpBidVolume1
		WHERE 1 ORDER BY id DESC LIMIT 1;
	#end if;
-- -------------------------------------------------------------------------------------------
#如果分钟数不相等 则认为新开始了一分钟 插入新的数据
else 
	if (mAskPrice1 != 0)&&( MOD(MinCompareTmp,MinConst)=0) then
		insert into IronDB.ag1506_5Min(
		InstrumentID,
		TradingDay,
		UpdateTime,
		MinuteNum,
		LastPrice,
		AskPrice1,
		BidPrice1,
		AskVolume1,
		BidVolume1,
		AveragePrice,
		ClosePrice,
		CurrDelta,
		ExchangeID,
		HighestPrice,
		LowestPrice,
		UpperLimitPrice,
		LowerLimitPrice,
		OpenInterest,
		OpenPrice,
		PreClosePrice,
		PreOpenInterest,
		PreSettlementPrice,
		StartVolume,
		EndVolume,
		Volume,
		SubDataNum
		) value(
		mInstrumentID,
		mTradingDay,
		mUpdateTime,
		Minute(mUpdateTime),			#开始分钟数为零select Minute(mUpdateTime) into MinCompare2;
		mLastPrice,
		mAskPrice1,
		mBidPrice1,
		mAskVolume1,
		mBidVolume1,
		mLastPrice,		#均价就是最新价
		mLastPrice,		#最新价就是收盘价
		mCurrDelta,
		mExchangeID,
		mLastPrice,		#最高价也是最新价
		mLastPrice,		#最低价也是最新价
		mUpperLimitPrice,
		mLowerLimitPrice,
		mOpeninterest,
		mLastPrice,		#开盘价格为当前价格
		mPreClosePrice,
		mPreOpeninterest,
		mPreSettlementPrice,
		mVolume,				#第一次为0 每次更新时为 openinterest - old openinterest + 当强vol
		mVolume,
		'0',
		'1'
		);
	end if;
end if;

END