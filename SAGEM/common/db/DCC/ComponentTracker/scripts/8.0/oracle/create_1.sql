/* Formatted on 2007/07/26 11:40 (Formatter Plus v4.8.8) */
-- **************************************/
-- *        Script - Common DB component - Evaluating table component_event
-- **************************************/

ALTER SESSION SET NLS_LENGTH_SEMANTICS='BYTE';


BEGIN
   DECLARE
      l_exists   VARCHAR (200);
      l_msg      VARCHAR (2000);
   BEGIN
      SELECT t.table_name
        INTO l_exists
        FROM user_tables t, user_tab_columns c
       WHERE t.table_name = c.table_name
         AND t.table_name = 'COMPONENT_EVENT'
         AND c.column_name = 'SUBCOMPONENT_LEVEL';

      EXECUTE IMMEDIATE 'DROP TABLE COMPONENT_EVENT';

      EXECUTE IMMEDIATE 'DROP SEQUENCE CMPNNTVNT_ID_SEQ';
   EXCEPTION
      WHEN NO_DATA_FOUND
      THEN
         NULL;
   END;
END;
/

BEGIN
   DECLARE
      l_exists   VARCHAR (200);
      l_msg      VARCHAR (2000);
   BEGIN
      SELECT sequence_name
        INTO l_exists
        FROM user_sequences
       WHERE sequence_name = 'CMPNNTVNT_ID_SEQ' ;
   EXCEPTION
      WHEN NO_DATA_FOUND
      THEN
         EXECUTE IMMEDIATE 'CREATE SEQUENCE CMPNNTVNT_ID_SEQ';

         COMMIT;
   END;
END;
/

BEGIN
   DECLARE
      l_exists   VARCHAR (200);
      l_msg      VARCHAR (2000);
   BEGIN
      SELECT table_name
        INTO l_exists
        FROM user_tables
       WHERE table_name = 'COMPONENT_EVENT';
   EXCEPTION
      WHEN NO_DATA_FOUND
      THEN
         EXECUTE IMMEDIATE    'CREATE TABLE COMPONENT_EVENT ( '
                           || '       COMPONENT_EVENT_ID   INTEGER NOT NULL,'
                           || '       COMPONENT_CD         VARCHAR2(50) NOT NULL,'
                           || '       COMPONENT_DESC       VARCHAR2(50) NULL,'
                           || '       COMPONENT_EVENT      VARCHAR2(30) NULL,'
                           || '       COMPONENT_LEVEL      VARCHAR2(30) NULL,'
			   || '       TABLESPACE_DATA      VARCHAR2(50) NULL,'
			   || '       TABLESPACE_INDEX     VARCHAR2(50) NULL,'			 
                           || '       EVENT_DT             DATE DEFAULT CURRENT_TIMESTAMP NOT NULL,'
                           || '       CTRL_INSERT_DT       DATE DEFAULT CURRENT_TIMESTAMP NOT NULL,'
                           || '       CTRL_UPDATE_DT       DATE DEFAULT CURRENT_TIMESTAMP NOT NULL'
                           || ')'
                           || '         TABLESPACE WEBMDATA';

         EXECUTE IMMEDIATE    'CREATE UNIQUE INDEX CMPNNTVNT_PKX ON COMPONENT_EVENT ('
                           || '       COMPONENT_EVENT_ID             ASC'
                           || ')'
                           || '         TABLESPACE WEBMINDX';

         EXECUTE IMMEDIATE    'ALTER TABLE COMPONENT_EVENT'
                           || '       ADD  ( CONSTRAINT CMPNNTVNT_PKX PRIMARY KEY ('
                           || '              COMPONENT_EVENT_ID)'
                           || '       USING INDEX'
                           || '         TABLESPACE WEBMINDX ) ';

         EXECUTE IMMEDIATE    'CREATE OR REPLACE TRIGGER CMPNNTVNT_RBI '
                           || '               BEFORE INSERT '
                           || '               ON COMPONENT_EVENT'
                           || '               FOR EACH ROW'
                           || '           BEGIN '
                           || '               SELECT CMPNNTVNT_ID_SEQ.NEXTVAL'
                           || '                 INTO :NEW.COMPONENT_EVENT_ID'
                           || '                 FROM DUAL;'
                           || '           END; ';

         EXECUTE IMMEDIATE    'CREATE OR REPLACE TRIGGER CMPNNTVNT_RBIU'
                           || '               BEFORE INSERT OR UPDATE'
                           || '               ON COMPONENT_EVENT'
                           || '               FOR EACH ROW'
                           || '           BEGIN  '
                           || '               :NEW.CTRL_UPDATE_DT := SYSDATE;'
                           || '               IF INSERTING'
                           || '               THEN'
                           || '                   :NEW.CTRL_INSERT_DT := SYSDATE;'
                           || '               END IF;'
                           || '           END;';

         COMMIT;
   END;
END;
/