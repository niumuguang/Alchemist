USE `IronDB`;
DELIMITER $$
CREATE DEFINER=`root`@`localhost` TRIGGER `ag1506_tick_AINS` AFTER INSERT ON `ag1506_tick`
FOR EACH ROW begin

#调用一分钟插入存储进程
call insertMin_ag1506(
new.InstrumentID,#varchar
new.TradingDay,#date
new.UpdateTime,#time
new.LastPrice,#float
new.AskPrice1,#float
new.BidPrice1,#float
new.AskVolume1,#int
new.BidVolume1,#int
new.AveragePrice,#float
new.ClosePrice,#float
new.CurrDelta,#float
new.ExchangeID,#char
new.HighestPrice,#float
new.LowestPrice,#float
new.UpperLimitPrice,#float
new.LowerLimitPrice,#float
new.OpenInterest,#int
new.OpenPrice,#float
new.PreClosePrice,#float
new.PreOpenInterest,#int
new.PreSettlementPrice,#float
new.Volume#int
);

#调用5分钟插入存储进程
call insert5Min_ag1506(
new.InstrumentID,#varchar
new.TradingDay,#date
/*
new.UpdateTime,#time
*/

new.LastPrice,#float
new.AskPrice1,#float
new.BidPrice1,#float
new.AskVolume1,#int
new.BidVolume1,#int
new.AveragePrice,#float
new.ClosePrice,#float
new.CurrDelta,#float
new.ExchangeID,#char
new.HighestPrice,#float
new.LowestPrice,#float
new.UpperLimitPrice,#float
new.LowerLimitPrice,#float
new.OpenInterest,#int
new.OpenPrice,#float
new.PreClosePrice,#float
new.PreOpenInterest,#int
new.PreSettlementPrice,#float
new.Volume#int*/
);

#调用15分钟插入存储进程
call insert15Min_ag1506(
new.InstrumentID,#varchar
new.TradingDay,#date
/*
new.UpdateTime,#time
*/
new.LastPrice,#float
new.AskPrice1,#float
new.BidPrice1,#float
new.AskVolume1,#int
new.BidVolume1,#int
new.AveragePrice,#float
new.ClosePrice,#float
new.CurrDelta,#float
new.ExchangeID,#char
new.HighestPrice,#float
new.LowestPrice,#float
new.UpperLimitPrice,#float
new.LowerLimitPrice,#float
new.OpenInterest,#int
new.OpenPrice,#float
new.PreClosePrice,#float
new.PreOpenInterest,#int
new.PreSettlementPrice,#float
new.Volume#int
);

end