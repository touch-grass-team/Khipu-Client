import psycopg
import os
import math
import subprocess
from click import BadParameter
from prettytable import PrettyTable, from_db_cursor
from prettytable import NONE

from src.config.connections import (
    DB_HOST_DEFAULT,
    DB_NAME_DEFAULT,
    DB_PASSWORD_DEFAULT,
    DB_USER_DEFAULT,
)

from src.config.width_settings import(
    id_part,
    timestamp_part,
    level_part,
    user_part,
    process_part,
    pid_part,
    message_part
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
            query = "SELECT * FROM syslog_ng.logs.prc_get_n_filtered_logs_ordered_by_time(%s, %s, %s, %s, %s, %s, %s);"
            req = cur.execute(
                query, args
            )
            table = from_db_cursor(req)
            table.align = "l"
            table.vrules = NONE
            screen_width=subprocess.run(['tput','cols'],capture_output=True,text=True)
            screen_width=float(screen_width.stdout)
            table._max_width={"_id" : math.floor(id_part*screen_width),
                                "_timestamp" : math.floor(timestamp_part*screen_width),
                                "_level" : math.floor(timestamp_part*screen_width),
                                "_user_name" : math.floor(user_part*screen_width),
                                "_process_name" : math.floor(process_part*screen_width),
                                "_pid" : math.floor(pid_part*screen_width),
                                "_message": math.floor(message_part*screen_width)}
            return table


def get_num_of_messages_by_level(host, *args) -> PrettyTable:
    if not host:
        host = DB_HOST_DEFAULT
    if len(args) != 4:
        raise BadParameter("You must specify all arguments!")
    with psycopg.connect(
        f"dbname={DB_NAME_DEFAULT} user={DB_USER_DEFAULT} password={DB_PASSWORD_DEFAULT} host={host}"
    ) as conn:
        with conn.cursor() as cur:
            query = "SELECT * FROM syslog_ng.logs.prc_get_stat_table_of_warnings(%s, %s, %s, %s);"
            req = cur.execute(
                query, args
            )
            table = from_db_cursor(req)
            table.align = "l"
            return table


def get_messages_stat(host, *args) -> PrettyTable:
    if not host:
        host = DB_HOST_DEFAULT
    if len(args) != 7:
        raise BadParameter("You must specify all arguments!")
    with psycopg.connect(
        f"dbname={DB_NAME_DEFAULT} user={DB_USER_DEFAULT} password={DB_PASSWORD_DEFAULT} host={host}"
    ) as conn:
        with conn.cursor() as cur:
            query = "SELECT * FROM syslog_ng.logs.prc_get_n_messages(%s ,%s, %s, %s, %s, %s, %s);"
            req = cur.execute(
                query, args
            )
            table = from_db_cursor(req)
            table.align = "l"
            table.vrules = NONE
            screen_width=subprocess.run(['tput','cols'],capture_output=True,text=True)
            screen_width=float(screen_width.stdout)
            table._max_width={"number_of_appear" : math.floor(0.05*screen_width),
                              "message" : math.floor(0.95*screen_width)}
            return table


