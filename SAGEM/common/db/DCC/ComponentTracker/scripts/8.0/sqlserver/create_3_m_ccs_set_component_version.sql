
DECLARE    @l_sql                          nvarchar (2000);
 
BEGIN

    IF EXISTS (select 1 from INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'COMPONENT_EVENT')
    BEGIN

        IF EXISTS (select 1 from INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'CCS_ENVIRONMENT')
        BEGIN 
            IF (SELECT count(COMPONENT_CD) FROM COMPONENT_EVENT WHERE COMPONENT_CD = 'CCS') = 0
            BEGIN 
                set @l_sql = 'INSERT INTO COMPONENT_EVENT (component_cd,component_desc,component_event,component_level) VALUES (''CCS'',''Central Configuration'',''INSTALL'', ''20'')'
                execute (@l_sql)
            END
        END

    END
END
   
GO


