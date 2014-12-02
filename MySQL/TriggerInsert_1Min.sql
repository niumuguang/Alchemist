USE `IronDB`;
DELIMITER $$
CREATE DEFINER=`root`@`localhost` TRIGGER `ag1506_1Min_BINS` BEFORE INSERT ON `ag1506_1Min`
FOR EACH ROW begin

declare tbName varchar(30) default "IronDB.ag1506_1Min";
declare CalMa3 float default 0;
#call CalculateMA3(tbName, CalMa3);
DECLARE mLast1MinPrice float default 0;
DECLARE mLast2MinPrice float default 0;
DECLARE mLast3MinPrice float default 0;
DECLARE resPrice float default 0;
DECLARE resMa5 float default 0;
DECLARE tmpP float default 0;
DECLARE i integer default 0;




while i<=2 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resPrice = resPrice + tmpP;
set i = i+1;
end while;
set new.MA3 = resPrice/3;

set tmpP = 0;
set i=0;

while i<=4 do
SELECT ClosePrice into tmpP FROM IronDB.ag1506_1Min ORDER BY id DESC LIMIT i,1;
set resMa5 = resMa5 + tmpP;
set i = i+1;
end while;
set new.MA5 = resMa5/5;

end