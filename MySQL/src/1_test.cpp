/*
1、创建数据库
create DATABASE wzq;
2、删除数据库
drop database wzq;
3、选择数据库
use wzq;

*/



/*
数据类型
    - 数值:
        严格数值数据类型(INTEGER、SMALLINT、DECIMAL 和 NUMERIC)
        近似数值数据类型(FLOAT、REAL 和 DOUBLE PRECISION)
    - 日期/时间
        DATETIME、DATE、TIMESTAMP、TIME和YEAR
    - 字符串(字符)类型
        CHAR、VARCHAR、BINARY、VARBINARY、BLOB、TEXT、ENUM和SET
*/

/*
1、创建数据表
CREATE TABLE table_name (column_name column_type);
2、删除数据表
DROP TABLE table_name ;
*/

/*
增：
INSERT INTO table_name ( field1, field2,...fieldN )
                       VALUES
                       ( value1, value2,...valueN );
*/

/*
查：
SELECT column_name,column_name
FROM table_name
[WHERE Clause]
[LIMIT N][ OFFSET M]

*/

/*
改：
UPDATE table_name SET field1=new-value1, field2=new-value2
[WHERE Clause]

*/

/*
删：
DELETE FROM table_name [WHERE Clause]

*/