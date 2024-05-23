from typing import List
from click import Group
import click
from src.commands.list.list import list_g

COMMANDS: List[Group] = [list_g]

