import click

from src.config.connections import DB_HOST_DEFAULT
from src.utils.call_sql import get_messages_stat

@click.group()
def stat_message_g():
    pass

@stat_message_g.command()
@click.option('--head', 'order',
              flag_value=False,
              default=True,
              help='Print old logs before new ones')
@click.option('--tail', 'order', 
              flag_value=True,
              help='Print new logs before old ones')
@click.option('--number','-n',
              type=int,
              show_default=True,
              help='Number of logs to show')
@click.option('--time','-t', "time",
              type=str,
              nargs=2,
              default = (None,None),
              help="Filter logs by period of time")
@click.option('--level','-l',"level",
              type=str,
              help='Filter logs by level')
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
def stat_message(order,number,time,level,user,service,database, host):
    """Message statistics"""
    data = get_messages_stat(host, order, number, *time, level, user,service)
    print(data)

