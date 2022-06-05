import requests
from pprint import pprint


class OsuClient:
    def __init__(self):
        self.base_url = "https://osu.ppy.sh/api/v2/"
        self.token_url = "https://osu.ppy.sh/oauth/token"
        self.token = self.__get_token()
        self.headers = {
            "Content-Type": "application/json",
            "Accept": "application/json",
            "Authorization": "Bearer " + self.token
        }
        self.params = dict()

    def __get_token(self):
        data = {
            "client_id": 10089,
            "client_secret": "CLIENT_SECRET_HERE",
            "grant_type": "client_credentials",
            "scope": "public",
            "code": "code"
        }
        a = requests.post(self.token_url, data=data)
        print(a.json()["expires_in"], "seconds to expire")
        return a.json()["access_token"]

    def __get_json(self, url):
        ret = requests.get(url, headers=self.headers, params=self.params)
        self.params.clear()
        return ret.json()

    def get_topscore(self, user_id: str, number: int):
        """
        :param user_id: id of any specific user
        :param number: number of top plays to return
        :return: plays for specified user
        """
        url = self.base_url + f"users/{user_id}/scores/best"
        self.params.update({"mode": "osu", "limit": number})
        return self.__get_json(url)

    def beatmap_lookup(self, checksum=None, filename=None, map_id=None):
        """
        :param checksum: checksum of the specific beatmap, safer than using map_id
        :param filename: don't know how to make it work // unusable for now
        :param map_id: id of the beatmap
        :return: Beatmap containing details about itself
        """
        url = self.base_url + "beatmaps/lookup"
        self.params.update({"checksum": checksum, "filename": filename, "id": map_id})
        return self.__get_json(url)

    def get_beatmap_scores(self, map_id: str, mods=None):
        """
        :param map_id: id of the beatmap
        :param mods: list of mods to specifically pick scores // currently not working.
        :return: list of BeatmapScores from top 50 in descending order
        """
        url = self.base_url + f"beatmaps/{map_id}/scores"
        self.params.update({"mode": "osu", "mods": mods})
        return self.__get_json(url)

    def search_user(self, keyword: str):
        """
        :param keyword: string to be searched for
        :return: returns the first user found that has the 'keyword' in their nickname
        """
        url = self.base_url + "search"
        self.params.update({"mode": "all", "query": keyword})
        return self.__get_json(url)["user"]["data"]


if __name__ == "__main__":
    client = OsuClient()
    x = client.get_beatmap_scores("2486881")


# map:sunglow, id:2486881
