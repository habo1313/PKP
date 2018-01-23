from distutils.core import setup
from Cython.Build import cythonize
from distutils.extension import Extension

sourcefiles = ['pkp.pyx']
compile_opts = ['-std=c++11']
ext = [Extension('*',
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
  ext_modules=cythonize(ext)
)
