from distutils.core import setup
from Cython.Build import cythonize
from distutils.extension import Extension

sourcefiles = ['cython/pkpc.pyx']
compile_opts = ['-std=c++11']
ext = [Extension('pkpc',
                 sourcefiles,
                 extra_compile_args=compile_opts,
                 extra_link_args=['-lpkp'],
                 library_dirs=['lib/'],
                 language='c++',
                 include_dirs=["src/"],
                 libraries=["pkp"]
                 )
       ]

setup(
    name="pkpc",
    ext_modules=cythonize(ext),
    description="FLUT Python class",
    author='Michele Vascellari',
    author_email='michele.vascellari@gmail.com',
    version="0.0.1"
)
