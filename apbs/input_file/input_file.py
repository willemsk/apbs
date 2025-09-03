from logging import getLogger
from pathlib import Path
from jsonschema import validate
from ruamel.yaml import YAML
from .calculate import calculate
from .process import process
from .read import read
from .check import check
from .membrane import membrane


_LOGGER = getLogger(__name__)


class InputFile:
    """
    The main class for parsing an APBS input file.
    """

    def __init__(self, path: str, check_path: bool = True):
        """
        Initialize the InputFile object.

        :param path: The path to the input file.
        :param check_path: Whether to check if the path exists.
        """
        self._path = path
        self._check_path = check_path
        self._dict = None
        self._schema = None
        self._load_schema()

    def _from_file(self):
        """
        Load the input file from the path.
        """
        if self._check_path and not Path(self._path).exists():
            raise FileNotFoundError(f"Input file not found: {self._path}")
        with open(self._path, "r") as f:
            yaml = YAML(typ="safe")
            self._dict = yaml.load(f)

    def _load_schema(self):
        """
        Load the schema for the input file.
        """
        path = Path(__file__).resolve().parent.parent.parent / "data" / "input-schema.json"
        if path.exists():
            with open(path, "r") as f:
                yaml = YAML(typ="safe")
                self._schema = yaml.load(f)
        else:
            _LOGGER.warning("Could not find input schema. Skipping validation.")


    def parse(self):
        """
        Parse the input file.
        """
        self._from_file()
        if self._schema:
            validate(self._dict, self._schema)
        if "read" in self._dict:
            read(self._dict["read"])
        if "calculate" in self._dict:
            calculate(self._dict["calculate"])
        if "process" in self._dict:
            process(self._dict["process"])
        if "check" in self._dict:
            check(self._dict["check"])
        if "membrane" in self._dict:
            membrane(self._dict["membrane"])
