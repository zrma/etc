import org.jetbrains.compose.compose
import org.jetbrains.compose.desktop.application.dsl.TargetFormat

plugins {
    kotlin("jvm") version "2.3.21"
    id("org.jetbrains.kotlin.plugin.compose") version "2.3.21"
    id("org.jetbrains.compose") version "1.9.3"
}

group = "team504.zrma"
version = "1.0"

repositories {
    google()
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test-testng"))
    implementation(compose.desktop.currentOs)
}

tasks.test {
    useTestNG()
}

kotlin {
    jvmToolchain(17)
}

compose.desktop {
    application {
        mainClass = "MainKt"
        nativeDistributions {
            targetFormats(TargetFormat.Dmg, TargetFormat.Msi, TargetFormat.Deb)
            packageName = "HelloCompose"
            packageVersion = "1.0.0"
        }
    }
}
