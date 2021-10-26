CREATE PROCEDURE SET_CCS_COMPONENT_VERSION()

LANGUAGE SQL

BEGIN

    DECLARE l_schema VARCHAR(25);
    DECLARE l_count INT DEFAULT 0;
    DECLARE l_stmt VARCHAR(1000);
    DECLARE c_ccs_check CURSOR FOR v_cur_stmt;
    
-- /***************************************************************************
-- ** Start
-- ***************************************************************************/
    VALUES CURRENT SCHEMA INTO l_schema;
    SET CURRENT PATH = l_schema;
    
    SELECT COUNT(*)  INTO l_count  FROM SYSCAT.TABLES
    WHERE TABSCHEMA = l_schema
    AND TABNAME = 'COMPONENT_EVENT';
    IF (l_count = 1) THEN
    
        SET l_count = 0;
        SELECT COUNT(*)  INTO l_count  FROM SYSCAT.TABLES
        WHERE TABSCHEMA = l_schema
        AND TABNAME = 'CCS_ENVIRONMENT';
        IF (l_count = 1 ) THEN
        
            SET l_count = 0;
            SET l_stmt = 'SELECT COUNT(*) FROM COMPONENT_EVENT WHERE COMPONENT_CD = ''CCS'' ';
            PREPARE v_cur_stmt FROM l_stmt;
            OPEN c_ccs_check;
            FETCH c_ccs_check INTO l_count;
            
            IF (l_count = 0 ) THEN

                SET l_stmt = 'INSERT INTO COMPONENT_EVENT (component_cd,component_desc,component_event,component_level) VALUES (''CCS'',''Central Configuration'',''INSTALL'', ''20'')';
                EXECUTE IMMEDIATE l_stmt; 
            END IF;
        END IF;
    END IF;   
END
/