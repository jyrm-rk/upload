declare
exists_fl varchar2(100); 
l_db_name varchar2(10);
l_banner varchar2(100);
l_user varchar2(30);
l_password varchar2(30);
l_sql varchar2(2000);
l_CURRENT_USER VARCHAR2 (100);
begin 
SELECT banner into l_banner FROM v$version where rownum=1;

	 IF l_banner is NOT NULL then
         l_db_name:='ORACLE';
		 l_user:=upper('&user');  
		 l_password:='&password';
	 ELSE
	     l_db_name:='TIBERO';
		 l_user:=upper('&user');  
		 l_password:='&password';
	END IF;
	
  begin 
        IF l_db_name ='ORACLE' THEN
        SELECT username INTO exists_fl FROM ALL_USERS WHERE username = upper('&user'); 
		ELSE
		        SELECT username INTO exists_fl FROM ALL_USERS WHERE username =l_user; 
        END IF;
    exception when no_data_found then 
        exists_fl := null;
    end; 

    if exists_fl is null and l_db_name ='ORACLE' then 
        execute immediate 'create user &user identified by &password DEFAULT TABLESPACE WEBMDATA TEMPORARY TABLESPACE TEMP'; 
	elsif exists_fl is null and l_db_name ='TIBERO' then 
		l_sql:='create user '|| l_user||' identified by '||l_password ||' DEFAULT TABLESPACE WEBMDATA TEMPORARY TABLESPACE TEMP';
        EXECUTE IMMEDIATE l_sql;    
    else
	    if exists_fl is null and l_db_name ='ORACLE' then 
        execute immediate 'alter user &user identified by &password DEFAULT TABLESPACE WEBMDATA TEMPORARY TABLESPACE TEMP'; 
		else
		l_sql:='alter user '|| l_user||' identified by '||l_password ||' DEFAULT TABLESPACE WEBMDATA TEMPORARY TABLESPACE TEMP';
        EXECUTE IMMEDIATE l_sql; 
        end if; 
    end if; 
-- Granting user permissions
 IF l_db_name ='ORACLE' THEN
execute immediate 'GRANT CREATE VIEW TO '||l_user;
execute immediate 'GRANT CREATE MATERIALIZED VIEW TO '||l_user;
execute immediate 'GRANT CREATE TABLE TO '||l_user;
execute immediate 'GRANT ALTER SESSION TO '||l_user;
execute immediate 'GRANT CREATE SESSION TO '||l_user;
execute immediate 'GRANT CREATE SYNONYM TO '||l_user;
execute immediate 'GRANT CREATE SEQUENCE TO '||l_user;
execute immediate 'GRANT CREATE DATABASE LINK TO '||l_user;
execute immediate 'GRANT CREATE TYPE TO '||l_user;
execute immediate 'GRANT CREATE TABLE TO '||l_user;
execute immediate 'GRANT CREATE TRIGGER TO '||l_user;
execute immediate 'GRANT CREATE OPERATOR TO '||l_user;
execute immediate 'GRANT CREATE INDEXTYPE TO '||l_user;
execute immediate 'GRANT CREATE PROCEDURE TO '||l_user;
execute immediate 'ALTER USER '||l_user ||' QUOTA UNLIMITED ON WEBMDATA';
execute immediate 'ALTER USER '||l_user ||' QUOTA UNLIMITED ON WEBMINDX';
ELSE
execute immediate 'GRANT CREATE VIEW TO '||l_user;
execute immediate 'GRANT CREATE MATERIALIZED VIEW TO '||l_user;
execute immediate 'GRANT CREATE TABLE TO '||l_user;
execute immediate 'GRANT ALTER SESSION TO '||l_user;
execute immediate 'GRANT CREATE SESSION TO '||l_user;
execute immediate 'GRANT CREATE SYNONYM TO '||l_user;
execute immediate 'GRANT CREATE SEQUENCE TO '||l_user;
execute immediate 'GRANT CREATE DATABASE LINK TO '||l_user;
execute immediate 'GRANT CREATE TYPE TO '||l_user;
execute immediate 'GRANT CREATE TABLE TO '||l_user;
execute immediate 'GRANT CREATE TRIGGER TO '||l_user;
execute immediate 'GRANT CREATE OPERATOR TO '||l_user;
execute immediate 'GRANT CREATE INDEXTYPE TO '||l_user;
execute immediate 'GRANT CREATE PROCEDURE TO '||l_user;
execute immediate 'ALTER USER '||l_user ||' QUOTA UNLIMITED ON WEBMDATA';
execute immediate 'ALTER USER '||l_user ||' QUOTA UNLIMITED ON WEBMINDX';
END IF;
END;

