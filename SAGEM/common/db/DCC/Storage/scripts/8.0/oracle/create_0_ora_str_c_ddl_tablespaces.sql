-- To create the webMethods tablespaces, one of these two must occur:    
--     1. The DB_CREATE_FILE_DEST parameter needs to be set for the Oracle instance    
--     2. The directory needs to be passed in as an argument    
-- By default, the parameter will be used    
--    
-- You will receive this error if neither of these two conditions is met:    
--    SVR4 Error: 2: No such file or directory    
declare dbfdst varchar2(100); 
exists_fl varchar2(100); 
l_db_name varchar2(10);
l_banner varchar2(100);
l_table_name varchar2(30);
l_sql varchar2(2000);
begin 
 SELECT banner into l_banner FROM v$version where rownum=1;

	 IF l_banner is NOT NULL then
         l_db_name:='ORACLE';
         l_table_name:='v$parameter';
	 ELSE
	     l_db_name:='TIBERO';
       l_table_name:='v$parameters';
	END IF;
    begin 
IF  l_db_name='ORACLE' then

	l_sql:='SELECT value INTO dbfdst FROM ' || l_table_name ||' WHERE name= ''db_create_file_dest''' ;  

ELSE
	l_sql:='SELECT value INTO dbfdst FROM '|| l_table_name ||' WHERE name= ''DB_CREATE_FILE_DEST''' ; 
    END IF;
    exception when no_data_found then 
        dbfdst := null; 
    end; 
    if dbfdst is null and l_db_name='ORACLE'  then 
        execute immediate 'alter session set db_create_file_dest=''&tablespacedir''' ; 
    end if; 
    begin 
        SELECT name INTO exists_fl FROM v$tablespace WHERE name= 'WEBMINDX' ; 
    exception when no_data_found then 
        exists_fl := null; 
    end; 
    if exists_fl is null then 
        execute immediate 'create tablespace WEBMINDX' ; 
    end if; 
    begin 
        SELECT name INTO exists_fl FROM v$tablespace WHERE name= 'WEBMDATA' ; 
    exception when no_data_found then 
        exists_fl := null; 
    end; 
    if exists_fl is null then 
        execute immediate 'create tablespace WEBMDATA' ; 
    end if; 
end ; 
/
