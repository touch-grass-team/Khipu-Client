import click

@click.command()
@click.option('--head', '-h','order',
              flag_value='lower',
              help='Print old logs before new ones')
@click.option('--tail', '-t','order', 
              flag_value='upper',
              default=True,
              help='Print new logs before old ones')
@click.option('--number','-n',
              default=50,
              type=int,
              show_default=True,
              help='Number of logs to show')
@click.option('--time','-t',
              type=str,
              nargs=2,
              help="Filter logs by period of time")
@click.option('--level','-l',
              default=30,
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
              show_default=True)

def khipu_list(order,number,time,level,user,service,database):
    """CLI for Khipu Log Analyzer"""
    if 

if __name__ == '__main__':
    khipu_list()

