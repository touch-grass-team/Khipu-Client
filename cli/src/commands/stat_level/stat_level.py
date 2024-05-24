import click

from src.config.connections import DB_HOST_DEFAULT
from src.utils.call_sql import get_num_of_messages_by_level

@click.group()
def stat_level_g():
    pass

@stat_level_g.command()
@click.option('--time','-t', "time",
              type=str,
              nargs=2,
              default = (None,None),
              help="Filter logs by period of time")
@click.option('--user','-u',
              type=str,
              help='Filter logs by user')
@click.option('--service','-s',
              type=str,
              help='Filter logs by service')
@click.option('--database','-d',
              default="syslog_ng",
              type=str,
              show_default=True,
              help="Database to connect to")
@click.option("--host", "host",
              type=str,
              default=DB_HOST_DEFAULT,
              help="Databse host",
              show_default=True)
def stat_level(time,user,service,database,host):
    """Level statistics"""
    data = get_num_of_messages_by_level(host,*time,user,service)
    print(data)

