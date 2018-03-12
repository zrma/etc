import * as _ from 'lodash';

const validCheck = (str: string) => {
    return _.isEmpty(str) ? "" : str.replace('/', '_');
};

export class File {
    file: string;
    title: string;

    constructor(file: string, title: string) {
        this.file = validCheck(file);
        this.title = validCheck(title);
    }
}

export class Movie {
    year: number;
    term: number;
    title: string;
    name: string;
    lecture: string;
    excerpt: string;
    videos: File[];

    constructor(year: number, term: number, title: string, name: string,
                lecture: string, excerpt: string, videos: string) {
        this.year = year;
        this.term = term;
        this.title = validCheck(title);
        this.name = validCheck(name);
        this.lecture = validCheck(lecture);
        this.excerpt = validCheck(excerpt);
        this.videos = JSON.parse(videos);
    }
}