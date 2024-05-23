import click
import os

@click.command()
@click.option('--head', '-h', 
              flag_value='lower'
              help='Print old logs before new ones')
@click.option('--tail', '-t', 
              flag_value='upper'
              help='Print new logs before old ones')
@click.option('--number','-n',
              default=50,
              type=int,
              show_default=true,
              help='Number of logs to show')
@click.option('--level','-n',
              default=30,
              type=str,
              help='Filter logs by level')
@click.option('--time','-t'
              type=str,
              default=)

@click.option('--database','-d',
              default="syslog_ng",
              type=str,
              show_default=true)
def hello(count, name):
    """Simple program that greets NAME for a total of COUNT times."""
    for x in range(count):
        click.echo(f"Hello {name}!")

if __name__ == '__main__':
    hello()

