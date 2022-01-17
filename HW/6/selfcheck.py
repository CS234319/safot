import pathlib
import zipfile
import os
import sys
import shutil
import argparse


def main():
    p = argparse.ArgumentParser()
    p.add_argument("zipfile")
    args = p.parse_args(sys.argv[1:])
    submission_file_name: str = args.zipfile
    if not submission_file_name.startswith("EX6_"):
        print("ERROR: bad file name")
        exit(1)
    DIR = "testing_submission_directory"
    if pathlib.Path(DIR).exists():
        shutil.rmtree(DIR)
    os.mkdir(DIR)

    if not pathlib.Path(submission_file_name).exists():
        print("ERROR: file doesnt exist")
        exit(1)

    print('checking for valid zipfile name, should be EX6_<taz1>_<taz2>.zip')
    tazs = submission_file_name[4:-4].split('_')
    for taz in tazs:
        if not taz.isdecimal() or len(taz) != 9:
            print("ERROR: {} is not a valid taz number".format(taz))
            exit(1)
        print('taz: {}'.format(taz))
    print("passed zipfile name test")

    print("extracting to directory named: testing_submission_directory !make sure it doesnt already exist!")
    with zipfile.ZipFile(submission_file_name, 'r') as zip_ref:
        zip_ref.extractall(DIR)
    print("extracted successfully")

    filenames = os.listdir(DIR)
    FILES = ["generators.py", "w6.py", "dry.pdf", "fermat.pl", "heaps.pl", "q3.pl"]
    for fn in FILES:
        if fn not in filenames:
            print(f'ERROR: {fn} file missing')
    redundant = set(filenames) - set(FILES)
    if redundant:
        print("ERROR: redundant files:", ", ".join(redundant))
    shutil.rmtree(DIR)


if __name__ == '__main__':
    main()
