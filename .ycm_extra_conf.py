import os

SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))

def ecosnail_include(project):
    return os.path.join(
        SCRIPT_DIR, 'deps', 'ecosnail', 'src', project, 'include')

FLAGS = [
    '-Wall',
    '-Wextra',
    '-x', 'c++',
    '-std=c++17',

    '-isystem', '/usr/include/c++/8.2.1',
    '-isystem', '/usr/include/c++/8.2.1/x86_64-pc-linux-gnu',
    '-isystem', '/usr/include/c++/8.2.1/backward',
    '-isystem', '/usr/include/',

    '-I', ecosnail_include('tail'),
]

def Settings(**kwargs):
    return {'flags': FLAGS}
