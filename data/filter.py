import pandas as pd

anime = pd.read_csv('anime-filtered.csv')
rating = pd.read_csv('rating.csv')

rating_filtered = rating[ rating['anime_id'].isin(anime['anime_id']) ]

rating_filtered.to_csv('rating-filtered.csv', index=False)
