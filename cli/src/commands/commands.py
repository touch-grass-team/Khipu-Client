from typing import List
from click import Group
import click
from src.commands.list.list import list_g
from src.commands.stat_message.stat_message import stat_message_g
from src.commands.stat_level.stat_level import stat_level_g

COMMANDS: List[Group] = [list_g,stat_message_g,stat_level_g]
