from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from create import Base
from insert import fill_database
from query import *
import argparse

DATABASE_URL = "postgresql://sun:1111@localhost:5432/work_hunter"

def create_tables(engine):
    try:
        Base.metadata.create_all(engine)
    except Exception as e:
        print(f"Error with create: {e}")

def drop_tables(engine):
    try:
        Base.metadata.drop_all(engine)
    except Exception as e:
        print(f"Error with delete: {e}")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--delete', action='store_true')
    parser.add_argument('--create', action='store_true')
    parser.add_argument('--fill', action='store_true')
    parser.add_argument('--select_all', type=str)
    parser.add_argument('-q', '--query', type=int, choices=range(1, 9), metavar='[1-8]')
    args = parser.parse_args()

    engine = create_engine(DATABASE_URL)

    if args.delete:
        drop_tables(engine)
    if args.create:
        create_tables(engine)
    if args.fill or args.query or args.select_all:
        local_session = sessionmaker(bind=engine)
        db = local_session()

        if args.fill:
            fill_database(db)
        if args.select_all:
            select_all(db, args.select_all)
        if args.query:
            execute_query(db, args.query)

        db.close()

if __name__ == "__main__":
    main()