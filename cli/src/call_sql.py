import psycopg

def get_filtered_n_logs():
    with psycopg.connect("dbname=syslog_ng user=log_reader password=client") as conn:
        with conn.cursor() as cur:
            cur.execute("SELECT syslog_ng.logs.select_n_filtered_logs_ordered_by_time(%s %s, %s, %s, %s, %s, %s)",
                         ()
        conn.commit()
        conn.close() 
