import click

from src.commands import COMMANDS

cli = click.CommandCollection(sources=COMMANDS)
if __name__ == "__main__":
    cli()
    # COMMANDS[0]()
