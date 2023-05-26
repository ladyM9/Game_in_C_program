#ifndef __LAB_H__
#define __LAB_H__

#include "ILI9341_STM32.h"
#include "stdio.h"
#include "maze.h"
#include "ball.h"

const myline_t lab1[80] = {{2.798259482601822, 3.2297342251706107, 137.11471464748928, 3.2297342251706107}, {159.50079050830385, 3.2297342251706107, 316.20332153400585, 3.2297342251706107}, {114.7286387866747, 29.0676080265355, 137.11471464748928, 29.0676080265355}, {181.88686636911842, 29.0676080265355, 226.65901809074757, 29.0676080265355}, {47.57041120423097, 54.90548182790039, 159.50079050830385, 54.90548182790039}, {204.272942229933, 54.90548182790039, 249.04509395156214, 54.90548182790039}, {25.184335343416397, 80.74335562926527, 47.57041120423097, 80.74335562926527}, {69.95648706504555, 80.74335562926527, 92.34256292586012, 80.74335562926527}, {114.7286387866747, 80.74335562926527, 204.272942229933, 80.74335562926527}, {249.04509395156214, 80.74335562926527, 271.4311698123767, 80.74335562926527}, {25.184335343416397, 106.58122943063016, 47.57041120423097, 106.58122943063016}, {69.95648706504555, 106.58122943063016, 92.34256292586012, 106.58122943063016}, {114.7286387866747, 106.58122943063016, 181.88686636911842, 106.58122943063016}, {204.272942229933, 106.58122943063016, 249.04509395156214, 106.58122943063016}, {271.4311698123767, 106.58122943063016, 293.8172456731913, 106.58122943063016}, {2.798259482601822, 132.41910323199505, 25.184335343416397, 132.41910323199505}, {92.34256292586012, 132.41910323199505, 114.7286387866747, 132.41910323199505}, {159.50079050830385, 132.41910323199505, 204.272942229933, 132.41910323199505}, {25.184335343416397, 158.25697703335993, 92.34256292586012, 158.25697703335993}, {114.7286387866747, 158.25697703335993, 137.11471464748928, 158.25697703335993}, {204.272942229933, 158.25697703335993, 271.4311698123767, 158.25697703335993}, {293.8172456731913, 158.25697703335993, 316.20332153400585, 158.25697703335993}, {47.57041120423097, 184.0948508347248, 69.95648706504555, 184.0948508347248}, {92.34256292586012, 184.0948508347248, 114.7286387866747, 184.0948508347248}, {137.11471464748928, 184.0948508347248, 159.50079050830385, 184.0948508347248}, {181.88686636911842, 184.0948508347248, 226.65901809074757, 184.0948508347248}, {249.04509395156214, 184.0948508347248, 316.20332153400585, 184.0948508347248}, {25.184335343416397, 209.93272463608972, 47.57041120423097, 209.93272463608972}, {69.95648706504555, 209.93272463608972, 181.88686636911842, 209.93272463608972}, {226.65901809074757, 209.93272463608972, 249.04509395156214, 209.93272463608972}, {271.4311698123767, 209.93272463608972, 293.8172456731913, 209.93272463608972}, {2.798259482601822, 235.7705984374546, 159.50079050830385, 235.7705984374546}, {181.88686636911842, 235.7705984374546, 316.20332153400585, 235.7705984374546}, {2.798259482601822, 3.2297342251706107, 2.798259482601822, 235.7705984374546}, {25.184335343416397, 3.2297342251706107, 25.184335343416397, 80.74335562926527}, {25.184335343416397, 158.25697703335993, 25.184335343416397, 209.93272463608972}, {47.57041120423097, 29.0676080265355, 47.57041120423097, 54.90548182790039}, {47.57041120423097, 80.74335562926527, 47.57041120423097, 132.41910323199505}, {47.57041120423097, 209.93272463608972, 47.57041120423097, 235.7705984374546}, {69.95648706504555, 3.2297342251706107, 69.95648706504555, 29.0676080265355}, {69.95648706504555, 54.90548182790039, 69.95648706504555, 80.74335562926527}, {69.95648706504555, 106.58122943063016, 69.95648706504555, 158.25697703335993}, {69.95648706504555, 184.0948508347248, 69.95648706504555, 209.93272463608972}, {92.34256292586012, 29.0676080265355, 92.34256292586012, 54.90548182790039}, {92.34256292586012, 158.25697703335993, 92.34256292586012, 184.0948508347248}, {114.7286387866747, 3.2297342251706107, 114.7286387866747, 29.0676080265355}, {114.7286387866747, 106.58122943063016, 114.7286387866747, 132.41910323199505}, {114.7286387866747, 158.25697703335993, 114.7286387866747, 184.0948508347248}, {137.11471464748928, 106.58122943063016, 137.11471464748928, 158.25697703335993}, {137.11471464748928, 184.0948508347248, 137.11471464748928, 209.93272463608972}, {159.50079050830385, 3.2297342251706107, 159.50079050830385, 54.90548182790039}, {159.50079050830385, 132.41910323199505, 159.50079050830385, 184.0948508347248}, {181.88686636911842, 29.0676080265355, 181.88686636911842, 54.90548182790039}, {181.88686636911842, 132.41910323199505, 181.88686636911842, 158.25697703335993}, {181.88686636911842, 184.0948508347248, 181.88686636911842, 235.7705984374546}, {204.272942229933, 54.90548182790039, 204.272942229933, 106.58122943063016}, {204.272942229933, 158.25697703335993, 204.272942229933, 184.0948508347248}, {204.272942229933, 209.93272463608972, 204.272942229933, 235.7705984374546}, {226.65901809074757, 3.2297342251706107, 226.65901809074757, 29.0676080265355}, {226.65901809074757, 54.90548182790039, 226.65901809074757, 80.74335562926527}, {226.65901809074757, 132.41910323199505, 226.65901809074757, 158.25697703335993}, {249.04509395156214, 29.0676080265355, 249.04509395156214, 54.90548182790039}, {249.04509395156214, 80.74335562926527, 249.04509395156214, 132.41910323199505}, {249.04509395156214, 184.0948508347248, 249.04509395156214, 209.93272463608972}, {271.4311698123767, 3.2297342251706107, 271.4311698123767, 80.74335562926527}, {271.4311698123767, 106.58122943063016, 271.4311698123767, 158.25697703335993}, {271.4311698123767, 209.93272463608972, 271.4311698123767, 235.7705984374546}, {293.8172456731913, 29.0676080265355, 293.8172456731913, 132.41910323199505}, {316.20332153400585, 3.2297342251706107, 316.20332153400585, 235.7705984374546}};
const myline_t lab2[75] = { {2.798259482601822, 3.2297342251706107, 137.11471464748928, 3.2297342251706107},{159.50079050830385, 3.2297342251706107, 316.20332153400585, 3.2297342251706107},{25.184335343416397, 29.0676080265355, 47.57041120423097, 29.0676080265355},{69.95648706504555, 29.0676080265355, 92.34256292586012, 29.0676080265355},{159.50079050830385, 29.0676080265355, 181.88686636911842, 29.0676080265355},{226.65901809074757, 29.0676080265355, 293.8172456731913, 29.0676080265355},{2.798259482601822, 54.90548182790039, 25.184335343416397, 54.90548182790039},{47.57041120423097, 54.90548182790039, 69.95648706504555, 54.90548182790039},{92.34256292586012, 54.90548182790039, 271.4311698123767, 54.90548182790039},{25.184335343416397, 80.74335562926527, 92.34256292586012, 80.74335562926527},{159.50079050830385, 80.74335562926527, 204.272942229933, 80.74335562926527},{271.4311698123767, 80.74335562926527, 293.8172456731913, 80.74335562926527},{2.798259482601822, 106.58122943063016, 25.184335343416397, 106.58122943063016},{69.95648706504555, 106.58122943063016, 92.34256292586012, 106.58122943063016},{114.7286387866747, 106.58122943063016, 159.50079050830385, 106.58122943063016},{181.88686636911842, 106.58122943063016, 204.272942229933, 106.58122943063016},{293.8172456731913, 106.58122943063016, 316.20332153400585, 106.58122943063016},{47.57041120423097, 132.41910323199505, 69.95648706504555, 132.41910323199505},{92.34256292586012, 132.41910323199505, 181.88686636911842, 132.41910323199505},{226.65901809074757, 132.41910323199505, 271.4311698123767, 132.41910323199505},{25.184335343416397, 158.25697703335993, 47.57041120423097, 158.25697703335993},{69.95648706504555, 158.25697703335993, 114.7286387866747, 158.25697703335993},{159.50079050830385, 158.25697703335993, 204.272942229933, 158.25697703335993},{226.65901809074757, 158.25697703335993, 249.04509395156214, 158.25697703335993},{47.57041120423097, 184.0948508347248, 92.34256292586012, 184.0948508347248},{137.11471464748928, 184.0948508347248, 226.65901809074757, 184.0948508347248},{249.04509395156214, 184.0948508347248, 293.8172456731913, 184.0948508347248},{25.184335343416397, 209.93272463608972, 69.95648706504555, 209.93272463608972},{114.7286387866747, 209.93272463608972, 137.11471464748928, 209.93272463608972},{159.50079050830385, 209.93272463608972, 204.272942229933, 209.93272463608972},{226.65901809074757, 209.93272463608972, 249.04509395156214, 209.93272463608972},{271.4311698123767, 209.93272463608972, 316.20332153400585, 209.93272463608972},{2.798259482601822, 235.7705984374546, 159.50079050830385, 235.7705984374546},{181.88686636911842, 235.7705984374546, 316.20332153400585, 235.7705984374546},{2.798259482601822, 3.2297342251706107, 2.798259482601822, 235.7705984374546},{25.184335343416397, 106.58122943063016, 25.184335343416397, 209.93272463608972},{47.57041120423097, 3.2297342251706107, 47.57041120423097, 54.90548182790039},{47.57041120423097, 106.58122943063016, 47.57041120423097, 132.41910323199505},{69.95648706504555, 54.90548182790039, 69.95648706504555, 80.74335562926527},{69.95648706504555, 106.58122943063016, 69.95648706504555, 158.25697703335993},{92.34256292586012, 29.0676080265355, 92.34256292586012, 54.90548182790039},{92.34256292586012, 158.25697703335993, 92.34256292586012, 235.7705984374546},{114.7286387866747, 3.2297342251706107, 114.7286387866747, 29.0676080265355},{114.7286387866747, 54.90548182790039, 114.7286387866747, 80.74335562926527},{114.7286387866747, 106.58122943063016, 114.7286387866747, 132.41910323199505},{114.7286387866747, 184.0948508347248, 114.7286387866747, 209.93272463608972},{137.11471464748928, 29.0676080265355, 137.11471464748928, 54.90548182790039},{137.11471464748928, 80.74335562926527, 137.11471464748928, 106.58122943063016},{137.11471464748928, 132.41910323199505, 137.11471464748928, 209.93272463608972},{159.50079050830385, 3.2297342251706107, 159.50079050830385, 29.0676080265355},{159.50079050830385, 54.90548182790039, 159.50079050830385, 80.74335562926527},{159.50079050830385, 209.93272463608972, 159.50079050830385, 235.7705984374546},{181.88686636911842, 80.74335562926527, 181.88686636911842, 106.58122943063016},{204.272942229933, 3.2297342251706107, 204.272942229933, 54.90548182790039},{204.272942229933, 106.58122943063016, 204.272942229933, 158.25697703335993},{226.65901809074757, 80.74335562926527, 226.65901809074757, 235.7705984374546},{249.04509395156214, 54.90548182790039, 249.04509395156214, 106.58122943063016},{271.4311698123767, 80.74335562926527, 271.4311698123767, 158.25697703335993},{293.8172456731913, 29.0676080265355, 293.8172456731913, 80.74335562926527},{293.8172456731913, 106.58122943063016, 293.8172456731913, 184.0948508347248},{316.20332153400585, 3.2297342251706107, 316.20332153400585, 235.7705984374546}};
const myline_t lab3[62] = { {25.184335343416397, 54.90548182790039, 47.57041120423097, 54.90548182790039},{69.95648706504555, 54.90548182790039, 92.34256292586012, 54.90548182790039},{114.7286387866747, 54.90548182790039, 159.50079050830385, 54.90548182790039},{181.88686636911842, 54.90548182790039, 204.272942229933, 54.90548182790039},{226.65901809074757, 54.90548182790039, 293.8172456731913, 54.90548182790039},{47.57041120423097, 80.74335562926527, 69.95648706504555, 80.74335562926527},{92.34256292586012, 80.74335562926527, 137.11471464748928, 80.74335562926527},{204.272942229933, 80.74335562926527, 316.20332153400585, 80.74335562926527},{25.184335343416397, 106.58122943063016, 69.95648706504555, 106.58122943063016},{92.34256292586012, 106.58122943063016, 181.88686636911842, 106.58122943063016},{2.798259482601822, 132.41910323199505, 25.184335343416397, 132.41910323199505},{69.95648706504555, 132.41910323199505, 159.50079050830385, 132.41910323199505},{204.272942229933, 132.41910323199505, 226.65901809074757, 132.41910323199505},{271.4311698123767, 132.41910323199505, 293.8172456731913, 132.41910323199505},{2.798259482601822, 158.25697703335993, 47.57041120423097, 158.25697703335993},{114.7286387866747, 158.25697703335993, 204.272942229933, 158.25697703335993},{249.04509395156214, 158.25697703335993, 271.4311698123767, 158.25697703335993},{293.8172456731913, 158.25697703335993, 316.20332153400585, 158.25697703335993},{25.184335343416397, 184.0948508347248, 47.57041120423097, 184.0948508347248},{92.34256292586012, 184.0948508347248, 114.7286387866747, 184.0948508347248},{204.272942229933, 184.0948508347248, 249.04509395156214, 184.0948508347248},{271.4311698123767, 184.0948508347248, 293.8172456731913, 184.0948508347248},{47.57041120423097, 209.93272463608972, 92.34256292586012, 209.93272463608972},{114.7286387866747, 209.93272463608972, 159.50079050830385, 209.93272463608972},{181.88686636911842, 209.93272463608972, 271.4311698123767, 209.93272463608972},{293.8172456731913, 209.93272463608972, 316.20332153400585, 209.93272463608972},{2.798259482601822, 235.7705984374546, 159.50079050830385, 235.7705984374546},{181.88686636911842, 235.7705984374546, 316.20332153400585, 235.7705984374546},{2.798259482601822, 3.2297342251706107, 2.798259482601822, 235.7705984374546},{25.184335343416397, 80.74335562926527, 25.184335343416397, 106.58122943063016},{25.184335343416397, 209.93272463608972, 25.184335343416397, 235.7705984374546},{47.57041120423097, 54.90548182790039, 47.57041120423097, 80.74335562926527},{47.57041120423097, 132.41910323199505, 47.57041120423097, 158.25697703335993},{47.57041120423097, 184.0948508347248, 47.57041120423097, 209.93272463608972},{69.95648706504555, 29.0676080265355, 69.95648706504555, 54.90548182790039},{69.95648706504555, 80.74335562926527, 69.95648706504555, 184.0948508347248},{92.34256292586012, 29.0676080265355, 92.34256292586012, 54.90548182790039},{92.34256292586012, 132.41910323199505, 92.34256292586012, 209.93272463608972},{114.7286387866747, 54.90548182790039, 114.7286387866747, 80.74335562926527},{114.7286387866747, 184.0948508347248, 114.7286387866747, 209.93272463608972},{137.11471464748928, 3.2297342251706107, 137.11471464748928, 54.90548182790039},{137.11471464748928, 158.25697703335993, 137.11471464748928, 184.0948508347248},{159.50079050830385, 54.90548182790039, 159.50079050830385, 80.74335562926527},{159.50079050830385, 184.0948508347248, 159.50079050830385, 235.7705984374546},{181.88686636911842, 29.0676080265355, 181.88686636911842, 235.7705984374546},{204.272942229933, 3.2297342251706107, 204.272942229933, 29.0676080265355},{204.272942229933, 80.74335562926527, 204.272942229933, 132.41910323199505},{226.65901809074757, 29.0676080265355, 226.65901809074757, 54.90548182790039},{226.65901809074757, 106.58122943063016, 226.65901809074757, 184.0948508347248},{249.04509395156214, 106.58122943063016, 249.04509395156214, 158.25697703335993},{271.4311698123767, 3.2297342251706107, 271.4311698123767, 29.0676080265355},{271.4311698123767, 80.74335562926527, 271.4311698123767, 132.41910323199505},{271.4311698123767, 158.25697703335993, 271.4311698123767, 209.93272463608972},{293.8172456731913, 29.0676080265355, 293.8172456731913, 54.90548182790039},{293.8172456731913, 106.58122943063016, 293.8172456731913, 132.41910323199505},{316.20332153400585, 3.2297342251706107, 316.20332153400585, 235.7705984374546},{1.399129741300911, 0.0, 4.197389223902733, 1.6148671125853054},{1.399129741300911, 4.8446013377559165, 1.399129741300911, 1.6148671125853054},{15.39042715431002, 368.1897016694496, 207.07120171253482, 1.6148671125853054},{1.399129741300911, 4.8446013377559165, 2798.2594826018217, 22.608139576194276},{12.592167671708198, 22.608139576194276, 12.592167671708198, 0.0}};
const myline_t lab4[80] = { {2.798259482601822, 3.2297342251706107, 137.11471464748928, 3.2297342251706107},{159.50079050830385, 3.2297342251706107, 316.20332153400585, 3.2297342251706107},{47.57041120423097, 29.0676080265355, 69.95648706504555, 29.0676080265355},{226.65901809074757, 29.0676080265355, 249.04509395156214, 29.0676080265355},{271.4311698123767, 29.0676080265355, 293.8172456731913, 29.0676080265355},{2.798259482601822, 54.90548182790039, 47.57041120423097, 54.90548182790039},{69.95648706504555, 54.90548182790039, 181.88686636911842, 54.90548182790039},{204.272942229933, 54.90548182790039, 226.65901809074757, 54.90548182790039},{293.8172456731913, 54.90548182790039, 316.20332153400585, 54.90548182790039},{25.184335343416397, 80.74335562926527, 47.57041120423097, 80.74335562926527},{92.34256292586012, 80.74335562926527, 137.11471464748928, 80.74335562926527},{181.88686636911842, 80.74335562926527, 293.8172456731913, 80.74335562926527},{25.184335343416397, 106.58122943063016, 92.34256292586012, 106.58122943063016},{137.11471464748928, 106.58122943063016, 159.50079050830385, 106.58122943063016},{226.65901809074757, 106.58122943063016, 249.04509395156214, 106.58122943063016},{293.8172456731913, 106.58122943063016, 316.20332153400585, 106.58122943063016},{47.57041120423097, 132.41910323199505, 69.95648706504555, 132.41910323199505},{114.7286387866747, 132.41910323199505, 159.50079050830385, 132.41910323199505},{181.88686636911842, 132.41910323199505, 204.272942229933, 132.41910323199505},{226.65901809074757, 132.41910323199505, 293.8172456731913, 132.41910323199505},{69.95648706504555, 158.25697703335993, 114.7286387866747, 158.25697703335993},{159.50079050830385, 158.25697703335993, 226.65901809074757, 158.25697703335993},{249.04509395156214, 158.25697703335993, 271.4311698123767, 158.25697703335993},{2.798259482601822, 184.0948508347248, 47.57041120423097, 184.0948508347248},{137.11471464748928, 184.0948508347248, 204.272942229933, 184.0948508347248},{226.65901809074757, 184.0948508347248, 249.04509395156214, 184.0948508347248},{25.184335343416397, 209.93272463608972, 69.95648706504555, 209.93272463608972},{114.7286387866747, 209.93272463608972, 159.50079050830385, 209.93272463608972},{204.272942229933, 209.93272463608972, 226.65901809074757, 209.93272463608972},{271.4311698123767, 209.93272463608972, 293.8172456731913, 209.93272463608972},{2.798259482601822, 235.7705984374546, 159.50079050830385, 235.7705984374546},{181.88686636911842, 235.7705984374546, 316.20332153400585, 235.7705984374546},{2.798259482601822, 3.2297342251706107, 2.798259482601822, 235.7705984374546},{25.184335343416397, 3.2297342251706107, 25.184335343416397, 29.0676080265355},{25.184335343416397, 106.58122943063016, 25.184335343416397, 158.25697703335993},{47.57041120423097, 54.90548182790039, 47.57041120423097, 80.74335562926527},{47.57041120423097, 132.41910323199505, 47.57041120423097, 184.0948508347248},{69.95648706504555, 29.0676080265355, 69.95648706504555, 106.58122943063016},{69.95648706504555, 158.25697703335993, 69.95648706504555, 209.93272463608972},{92.34256292586012, 3.2297342251706107, 92.34256292586012, 29.0676080265355},{92.34256292586012, 106.58122943063016, 92.34256292586012, 158.25697703335993},{92.34256292586012, 184.0948508347248, 92.34256292586012, 235.7705984374546},{114.7286387866747, 29.0676080265355, 114.7286387866747, 54.90548182790039},{114.7286387866747, 80.74335562926527, 114.7286387866747, 209.93272463608972},{137.11471464748928, 3.2297342251706107, 137.11471464748928, 29.0676080265355},{137.11471464748928, 158.25697703335993, 137.11471464748928, 184.0948508347248},{159.50079050830385, 29.0676080265355, 159.50079050830385, 106.58122943063016},{159.50079050830385, 132.41910323199505, 159.50079050830385, 158.25697703335993},{159.50079050830385, 209.93272463608972, 159.50079050830385, 235.7705984374546},{181.88686636911842, 29.0676080265355, 181.88686636911842, 54.90548182790039},{181.88686636911842, 80.74335562926527, 181.88686636911842, 106.58122943063016},{181.88686636911842, 184.0948508347248, 181.88686636911842, 235.7705984374546},{204.272942229933, 3.2297342251706107, 204.272942229933, 54.90548182790039},{204.272942229933, 80.74335562926527, 204.272942229933, 132.41910323199505},{226.65901809074757, 106.58122943063016, 226.65901809074757, 184.0948508347248},{226.65901809074757, 209.93272463608972, 226.65901809074757, 235.7705984374546},{249.04509395156214, 3.2297342251706107, 249.04509395156214, 54.90548182790039},{249.04509395156214, 184.0948508347248, 249.04509395156214, 209.93272463608972},{271.4311698123767, 29.0676080265355, 271.4311698123767, 132.41910323199505},{271.4311698123767, 158.25697703335993, 271.4311698123767, 235.7705984374546},{293.8172456731913, 132.41910323199505, 293.8172456731913, 184.0948508347248},{316.20332153400585, 3.2297342251706107, 316.20332153400585, 235.7705984374546},{1.399129741300911, 0.0, 4.197389223902733, 1.6148671125853054},{1.399129741300911, 4.8446013377559165, 1.399129741300911, 1.6148671125853054},{15.39042715431002, 368.1897016694496, 207.07120171253482, 1.6148671125853054},{1.399129741300911, 4.8446013377559165, 2798.2594826018217, 22.608139576194276},{12.592167671708198, 22.608139576194276, 12.592167671708198, 0.0},{2.798259482601822, 3.2297342251706107, 2.798259482601822, 158.25697703335993}};

const myline_t *labirint[] = {lab1, lab2, lab3, lab4};
const myline_t exitLine[] = {{160, 235, 175, 235}};
int labElements[4] = {(sizeof(lab1)) / (sizeof(myline_t)), (sizeof(lab2)) / (sizeof(myline_t)),(sizeof(lab3)) / (sizeof(myline_t)), (sizeof(lab4)) / (sizeof(myline_t))};
int labExitEl[1] = { (sizeof(exitLine)) / (sizeof(myline_t))};
#endif