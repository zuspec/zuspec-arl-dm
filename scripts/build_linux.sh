#!/bin/sh -x

yum install -y glibc-static ninja-build

echo "BUILD_NUM=${BUILD_NUM}" >> python/zsp_arl_dm/__build_num__.py
${IVPM_PYTHON} -m pip install ivpm cython setuptools --pre
echo "IVPM version: (1)"
${IVPM_PYTHON} -m pip show ivpm
${IVPM_PYTHON} -m ivpm update -a --py-prerls-packages

PYTHON=./packages/python/bin/python

echo "IVPM version: (2)"
${PYTHON} -m pip show ivpm
${PYTHON} -m pip install --upgrade --pre ivpm
echo "IVPM version: (3)"
${PYTHON} -m pip show ivpm
${PYTHON} -m pip install twine auditwheel ninja wheel cython
${PYTHON} setup.py bdist_wheel

for whl in dist/*.whl; do
    ${PYTHON} -m auditwheel repair --only-plat $whl
    rm $whl
done
