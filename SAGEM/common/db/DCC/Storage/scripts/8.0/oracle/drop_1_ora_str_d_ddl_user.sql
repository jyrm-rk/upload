-- Drop user

declare exists_fl varchar2(100); 
begin 
    begin 
        SELECT username INTO exists_fl FROM ALL_USERS WHERE username = upper('&user'); 
    exception when no_data_found then 
        exists_fl := null;
    end; 

    if exists_fl is not null then 
        execute immediate 'drop user &user cascade';
    end if; 
end ;
/
