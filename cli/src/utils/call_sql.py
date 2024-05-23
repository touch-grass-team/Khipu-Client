import psycopg
from click import BadParameter
from prettytable import PrettyTable, from_db_cursor

from src.config.connections import (
    DB_HOST_DEFAULT,
    DB_NAME_DEFAULT,
    DB_PASSWORD_DEFAULT,
    DB_USER_DEFAULT,
)


def get_filtered_n_logs(host, *args) -> PrettyTable:
    if not host:
        host = DB_HOST_DEFAULT
    if len(args) != 7:
        raise BadParameter("You must specify all arguments!")
    with psycopg.connect(
        f"dbname={DB_NAME_DEFAULT} user={DB_USER_DEFAULT} password={DB_PASSWORD_DEFAULT} host={host}"
    ) as conn:
        with conn.cursor() as cur:
            query = "SELECT * FROM syslog_ng.logs.select_n_filtered_logs_ordered_by_time(%s, %s, %s, %s, %s, %s, %s);"
            req = cur.execute(
                query, args
            )
            table = from_db_cursor(req)
            table.align = "l"
            table._max_width = {"_message": 70}
            return table
