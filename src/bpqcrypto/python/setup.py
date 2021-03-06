# Copyright (c) 2018 The PsiChain developers

import os
import os.path
import sys
import glob
import setuptools
from setuptools import setup
#from setuptools import setup, Distribution
from setuptools.dist import Distribution

BPQ_CRYPTO_VERSION = "1.3.3"


class BinaryDistribution(Distribution):

    def is_pure(self):
        return False

    def has_ext_modules(self):
        return True


def main():

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    package_name = "psicrypto"

    with open("README.md", "r") as fh:
        long_description = fh.read()

    packages = ['psicrypto']

    if sys.platform == 'win32':
        package_data = {
            'psicrypto': ['psicrypto.dll'],
        }
    elif sys.platform == 'darwin':
        package_data = {
            'psicrypto': ['libpsicrypto.dylib'],
        }
    else:
        package_data = {
            'psicrypto': ['libpsicrypto.so'],
        }

    if sys.platform == "win32":
        classifiers = (
            "Development Status :: 4 - Beta",
            "Environment :: Console",
            'Intended Audience :: Information Technology',
            "Programming Language :: Python :: 3 :: Only",
            "Programming Language :: Python :: Implementation :: CPython",
            'Programming Language :: C++',
            "License :: OSI Approved :: MIT License",
            "Operating System :: Microsoft :: Windows :: Windows 10",
            'Topic :: Security',
            'Topic :: Security :: Cryptography',
            'Topic :: Software Development',
        )
    elif sys.platform == "linux":
        classifiers = (
            "Development Status :: 4 - Beta",
            "Environment :: Console",
            'Intended Audience :: Information Technology',
            "Programming Language :: Python :: 3 :: Only",
            "Programming Language :: Python :: Implementation :: CPython",
            'Programming Language :: C++',
            "License :: OSI Approved :: MIT License",
            "Operating System :: Unix",
            'Topic :: Security',
            'Topic :: Security :: Cryptography',
            'Topic :: Software Development',
        )
    elif sys.platform == "darwin":
        classifiers = (
            "Development Status :: 4 - Beta",
            "Environment :: Console",
            'Intended Audience :: Information Technology',
            "Programming Language :: Python :: 3 :: Only",
            "Programming Language :: Python :: Implementation :: CPython",
            'Programming Language :: C++',
            "License :: OSI Approved :: MIT License",
            "Operating System :: MacOS",
            "Operating System :: MacOS :: MacOS X",
            'Topic :: Security',
            'Topic :: Security :: Cryptography',
            'Topic :: Software Development',
        )
    else:
        raise Exception("unsupported platform")

    setup(
        name="psicrypto",
        version=BPQ_CRYPTO_VERSION,
        author="psichain",
        author_email="dev@psichain.org",
        description="a crypto library for BPQ",
        long_description=long_description,
        #long_description_content_type="text/markdown",
        url="https://github.com/PsiChain/PsiChain",
        classifiers=classifiers,
        project_urls={
            'Source': 'https://github.com/PsiChain/PsiChain',
            'Tracker': 'https://github.com/PsiChain/PsiChain/issues',
        },
        python_requires='>=3',
        packages=packages,
        package_data=package_data,
        include_package_data=True,
        distclass=BinaryDistribution,
    )


if __name__ == "__main__":

    main()
