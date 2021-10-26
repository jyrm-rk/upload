-- Tablespace must be empty to drop

declare exists_fl varchar2(100); 
begin 
    begin 
        SELECT name INTO exists_fl FROM v$tablespace WHERE name= 'WEBMDATA' ; 
    exception when no_data_found then 
        exists_fl := null; 
    end; 
    if exists_fl is not null then 
        execute immediate 'drop tablespace WEBMDATA' ; 
    end if; 
    begin 
        SELECT name INTO exists_fl FROM v$tablespace WHERE name= 'WEBMINDX' ; 
    exception when no_data_found then 
        exists_fl := null; 
    end; 
    if exists_fl is not null then 
        execute immediate 'drop tablespace WEBMINDX' ; 
    end if; 
end ; 
/
