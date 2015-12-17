import importlib
import sys

_sysconfigdata = importlib.import_module("_sysconfigdata_%s" % sys.abiflags)
globals().update({k: v for k, v in _sysconfigdata.__dict__.items() if not k.startswith("_")})
del importlib, sys, _sysconfigdata
