import {execAsync} from 'async-child-process';
import {PromisePool} from 'es6-promise-pool';
import * as path from 'path';

import * as fs from 'fs-extra';
import * as _ from 'lodash';
import * as sleep from 'sleep-promise';

import * as csv from 'csvtojson';
import {File, Movie} from './movie';

import * as Raven from 'raven';

Raven.config('https://c6d70268440f40da8d0a3edabaac8f34:4c9871dda7594070af88d9d53d5e13d5@sentry.team504.co.kr//3')
    .install();

const filePath = path.join(__dirname, 'portal.csv');
const logger = console;

const loadMovies = async () => {
    const data: Movie[] = [];

    csv().fromFile(filePath).on('json', (jsonObj: Movie) => {
        data.push(jsonObj);
    });

    await sleep(500);
    return data;
};

(async function start() {
    const rawMovies = await loadMovies();

    const movies = _.map(rawMovies, (item: any) => {
        return new Movie(item.year, item.term, item.title, item.name, item.lecture, item.excerpt, item.videos);
    });

    const outputRoot = '/Users/name/Downloads/movies';
    await fs.ensureDir(outputRoot);

    const nameFilter = (file: File) => {
        return (file.file.endsWith('null') || file.file.endsWith('avi'));
    };

    const invalidFilter = (movie: Movie) => {
        return _.isEmpty(movie.videos) || _.every(movie.videos, nameFilter);
    };

    const invalidMovies = _.filter(movies, invalidFilter);
    logger.log('유효성 체크 실패, 무시 목록');
    logger.log('----------------------------------------');

    _.each(invalidMovies, (movie) => {
        const msg = `${movie.year}년 ${movie.term}학기 - ${movie.title}_${movie.name} [${movie.lecture}]`;
        logger.log(msg);
    });
    logger.log('----------------------------------------');

    const validMovies = _.filter(movies, (movie) => {
        return !invalidFilter(movie);
    });

    const commands: string[] = [];
    _.each(validMovies, async (movie) => {
        const currentPath = path.join(outputRoot, `${movie.year}/${movie.term}`,
            `${movie.title}_${movie.name}`, `${movie.lecture}`);
        await fs.ensureDir(currentPath);

        const readmeData = `
----------------------------------------
${movie.year}년 ${movie.term}학기
----------------------------------------
과목 : ${movie.title}
교수 : ${movie.name}

${movie.lecture}
----------------------------------------
세부사항 ${!_.isEmpty(movie.excerpt) ? '- ' : ''}${movie.excerpt}
----------------------------------------
파일 목록
`;
        const readmePath = path.join(currentPath, `readme.md`);
        if (await fs.pathExists(readmePath)) {
            await fs.remove(readmePath);
        }

        await fs.writeFile(readmePath, readmeData);

        if (!_.isEmpty(movie.videos)) {
            _.times(movie.videos.length, async (idx: number) => {
                if (nameFilter(movie.videos[idx])) {
                    return;
                }
                await fs.appendFile(readmePath, `\n${idx + 1}.mp4`);
            });

            _.each(movie.videos, (file: File, idx: number) => {
                if (nameFilter(file)) {
                    return;
                }

                const [host, instance] = file.file.split('mp4:');
                // noinspection SpellCheckingInspection
                const cmd = `rtmpdump -r "${host}" -y "mp4:${instance}" -o "${currentPath}/${idx + 1}.mp4"`;
                commands.push(cmd);
            });
        }
    });

    const task = async (cmd: string) => {
        logger.log(cmd);
        return new Promise(async (resolve) => {
            try {
                await execAsync(cmd, {maxBuffer: 500 * 1024 * 1024});
                return resolve();
            } catch (e) {
                console.error('[*failed*]', cmd);
                return resolve();
            }
        });
    };

    const maxCnt = commands.length;
    let cnt = 0;

    const promiseProducer = () => {
        if (cnt < maxCnt) {
            return task(commands[cnt++]);
        } else {
            return null;
        }
    };

    const concurrency = 20;
    const pool = new PromisePool(promiseProducer, concurrency);
    pool.start()
        .then(() => {
            logger.log('Complete');
        });
})();
