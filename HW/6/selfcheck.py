import zipfile
import os
import sys
import shutil


def main():
    submission_file_name = sys.argv[1]
    os.mkdir("testing_submission_directory")

    print('checking for valid zipfile name, should be EX6_<taz1>_<taz2>.zip')
    tazs = submission_file_name[4:-4].split('_')
    for taz in tazs:
        if not taz.isdecimal() or len(taz) != 9:
            print("{} is not a valid taz number".format(taz))
            exit(1)
        print('taz: {}'.format(taz))
    print("passed zipfile name test")

    print("extracting to directory named: testing_submission_directory !make sure it doesnt already exists!")
    with zipfile.ZipFile(submission_file_name, 'r') as zip_ref:
        zip_ref.extractall("testing_submission_directory")
    print("extracted successfully")

    filenames = os.listdir("testing_submission_directory")
    FILES = ["generators.py", "w6.py", "dry.pdf", "fermat.pl", "heaps.pl", "q3.pl"]
    for fn in FILES:
        if fn not in filenames:
            print(f'{fn} file missing')
    redundant = set(filenames) - set(FILES)
    if redundant:
        print("redundant files:", ", ".join(redundant))
    shutil.rmtree("testing_submission_directory")
    print('zip is ready for submission!')


if __name__ == '__main__':
    main()
