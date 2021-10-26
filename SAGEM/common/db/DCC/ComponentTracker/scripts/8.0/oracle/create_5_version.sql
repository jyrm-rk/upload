BEGIN
 DECLARE v_count NUMBER(1) := 0;
 BEGIN
 SELECT 1
 INTO v_count
 FROM USER_TABLES
 WHERE table_name = 'CCS_ENVIRONMENT'
 AND 0  =  (SELECT count(COMPONENT_CD) FROM COMPONENT_EVENT WHERE COMPONENT_CD = 'CCS');
IF v_count = 1 THEN
  EXECUTE IMMEDIATE 'INSERT INTO COMPONENT_EVENT (component_cd,component_desc,component_event,component_level) VALUES (''CCS'',''Central Configuration'',''INSTALL'', ''20'')';
  COMMIT;
END IF;
EXCEPTION
 WHEN OTHERS THEN 
v_count := 0;
 END;
END;
/
