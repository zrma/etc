package com.example.chapter8

import org.apache.spark.mllib.feature.{Word2Vec, Word2VecModel}
import org.apache.spark.mllib.linalg.Vectors
import org.apache.spark.sql.SparkSession
import org.openkoreantext.processor.OpenKoreanTextProcessor
import org.openkoreantext.processor.phrase_extractor.KoreanPhraseExtractor.KoreanPhrase
import org.openkoreantext.processor.tokenizer.KoreanTokenizer.KoreanToken

// 단어를 계산 가능하도록 벡터로 변환(숫자화)하는 알고리즘
// 문장의 다음에 올 단어를 예측하는 Word2Vec 모델에 사용한다
object SimpleWord2Vec {
  private def practiceKoreanProcessor(): Unit = {
    val sentence = "이 책은 무슨 책입니까"

    // Normalize
    val normalized: CharSequence = OpenKoreanTextProcessor.normalize(sentence)
    println(normalized)

    // Tokenize
    val tokens: Seq[KoreanToken] = OpenKoreanTextProcessor.tokenize(normalized)
    println(tokens)

    // Phrase extraction
    val phrases: Seq[KoreanPhrase] =
      OpenKoreanTextProcessor.extractPhrases(
        tokens,
        filterSpam = true,
        enableHashtags = true
      )
    println(phrases)
  }

  private def relationWords(w1: String,
                            w2: String,
                            target: String,
                            model: Word2VecModel) = {
    val a = breeze.linalg.Vector(model.getVectors(w2))
    val b = breeze.linalg.Vector(model.getVectors(w1))
    val c = breeze.linalg.Vector(model.getVectors(target))

    // w1 -> w2 벡터에 target을 합성해 원하는 x값을 찾는다.
    val x = c + (a - b)
    model.findSynonyms(Vectors.dense(x.toArray.map(_.toDouble)), 10)
  }

  def main(args: Array[String]): Unit = {
    practiceKoreanProcessor()

    val ss = SparkSession
      .builder()
      .master("local[*]")
      .appName("Word2Vec")
      .getOrCreate()

    val input = ss.sparkContext
      .textFile("data/chapter8/words_data.txt")
      .map(
        line =>
          OpenKoreanTextProcessor.tokensToStrings(
            OpenKoreanTextProcessor
              .tokenize(OpenKoreanTextProcessor.normalize(line))
          )
      )

    val word2vec = new Word2Vec()
    word2vec.setMinCount(3)
    word2vec.setVectorSize(30)
    val model = word2vec.fit(input)

    input.foreach(println)

    println(model.findSynonyms("나", 3).mkString(","))
    println(model.findSynonyms("어머니", 3).mkString(","))

    println(relationWords("어머니", "별", "나", model).mkString(","))
  }
}
