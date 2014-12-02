USE `IronDB`;
DELIMITER $$


CREATE DEFINER=`root`@`localhost` TRIGGER `ag1506_1Min_BUPD` BEFORE UPDATE ON `ag1506_1Min`
FOR EACH ROW begin

declare tbName varchar(30) default "IronDB.ag1506_1Min";
declare CalMa3 float default 0;
#call CalculateMA3(tbName, CalMa3);
DECLARE mHighestPrice float default 0;
DECLARE mLowestPrice float default 0;
#DECLARE mLast3MinPrice float default 0;
DECLARE resPrice float default 0;
DECLARE resMa3 float default 0;
DECLARE resMa5 float default 0;
DECLARE resMa8 float default 0;
DECLARE resMa13 float default 0;
DECLARE resMa21 float default 0;
DECLARE resMa34 float default 0;
DECLARE resMa55 float default 0;
DECLARE resMa89 float default 0;
DECLARE tmpP float default 0;
DECLARE i integer default 0;
#
declare stdMa float default 0;
declare stdTmp float default 0;
declare stdPower float default 0;

-- 只有更新触发器 时比较最高价和最低价
#获取最高价和最低价
SELECT HighestPrice into mHighestPrice FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT 0,1;
SELECT LowestPrice into mLowestPrice FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT 0,1;
#最高价
if new.LastPrice > mHighestPrice then
	set new.HighestPrice = new.LastPrice;
else
	set new.HighestPrice = mHighestPrice;
end if;
#最低价
if new.LastPrice < mLowestPrice then
	set new.LowestPrice = new.LastPrice;
else
	set new.LowestPrice = mLowestPrice;
end if;

-- ----------------------------------------------------------------------------
# MA3
while i<=2 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa3 = resMa3 + tmpP;
set i = i+1;
end while;
set new.MA3 = resMa3/3;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
# MA5
while i<=4 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa5 = resMa5 + tmpP;
set i = i+1;
end while;
set new.MA5 = resMa5/5;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
# MA8
while i<=7 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa8 = resMa8 + tmpP;
set i = i+1;
end while;
set new.MA8 = resMa8/8;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
# MA13
while i<=12 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa13 = resMa13 + tmpP;
set i = i+1;
end while;
set new.MA13 = resMa13/13;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
# MA21
while i<=20 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa21 = resMa21 + tmpP;
set i = i+1;
end while;
set new.MA21 = resMa21/21;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
# MA34
while i<=33 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa34 = resMa34 + tmpP;
set i = i+1;
end while;
set new.MA34 = resMa34/34;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
# MA55
while i<=54 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa55 = resMa55 + tmpP;
set i = i+1;
end while;
set new.MA55 = resMa55/55;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
# MA89
while i<=88 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa89 = resMa89 + tmpP;
set i = i+1;
end while;
set new.MA89 = resMa89/89;
set tmpP = 0;
set i=0;
-- ----------------------------------------------------------------------------
-- ----------------------------------------------------------------------------
#标准差 26天平均价
while i<=25 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set stdMa = stdMa + tmpP;
set i = i+1;
end while;
set stdMa = stdMa/26;
set new.BollMid = stdMa;
-- ----------------------------
set tmpP = 0;
set i=0;
while i<=25 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set stdTmp = tmpP - stdMa;
set stdPower = stdPower + power(stdTmp);
set i = i+1;
end while;
set stdTmp = stdPower/26;
set stdTmp = sqrt(stdTmp);
set new.BollUp = stdMa + stdTmp;
set new.BollDown = stdMa - stdTmp;

end