DELETE FROM component_event
      WHERE component_cd = 'CMN';

UPDATE component_event
   SET component_level = '15'
 WHERE component_cd IN ('OPM', 'DBM', 'DTP', 'ARC') AND component_level LIKE '6.5.%';


UPDATE component_event
   SET component_level = '10'
 WHERE component_level LIKE '6.5.%';

COMMIT ;
