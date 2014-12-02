-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE FUNCTION `TimeMachine` ( nHour int(2), nMinute int(2), nSecond int(2),
								oHour int(2), oMinute int(2), oSecond int(2) )
RETURNS bool

BEGIN



RETURN False;
END