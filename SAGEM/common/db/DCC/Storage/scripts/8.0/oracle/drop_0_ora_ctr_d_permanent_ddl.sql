-- **************************************/  
-- *        Script - Common DB component - Evaluating table component_event  
-- **************************************/  
BEGIN 
    BEGIN 
        EXECUTE IMMEDIATE 'DROP TABLE &user.COMPONENT_EVENT'; 
    EXCEPTION 
    WHEN OTHERS THEN 
        NULL; 
    END; 
    BEGIN 
        EXECUTE IMMEDIATE 'DROP SEQUENCE &user.CMPNNTVNT_ID_SEQ'; 
    EXCEPTION 
    WHEN OTHERS THEN 
        NULL; 
    END; 
    BEGIN 
        EXECUTE IMMEDIATE 'DROP VIEW &user.INSTALLED_COMPONENT'; 
    EXCEPTION 
    WHEN OTHERS THEN 
        NULL; 
    END; 
END; 
/ 