## 1. Now using pyproject

To list all installed packages wrtite to requirement.txt
    pip freeze > requirements.txt

## 2. Build 
python -m build

This is normal installation : 
pip install dist/my_project-0.1.0-py3-none-any.whl

This is development installation:
pip install -e .

