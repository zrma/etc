<template>
  <div id="wrapper">
    <img id="logo" src="~@/assets/logo.png" alt="electron-vue">
    <main>
      <div class="left-side">
        <span class="title">
                Welcome to your new project!
              </span>
        <system-information></system-information>
      </div>
  
      <div class="right-side">
        <div class="doc">
          <div class="title">Getting Started</div>
          <p>
            electron-vue comes packed with detailed documentation that covers everything from internal configurations, using the project structure, building your application, and so much more.
          </p>
          <ul id="example">
            <li class="example" v-for="item in results" :key="item">
              <div><icon name="share"></icon></div>
              {{ item }}
            </li>
          </ul>
          <button @click="open('https://simulatedgreg.gitbooks.io/electron-vue/content/')">Read the Docs</button><br><br>
        </div>
        <div class="doc">
          <div class="title alt">Other Documentation</div>
          <button class="alt" @click="open('https://electron.atom.io/docs/')">Electron</button>
          <button class="alt" @click="open('https://vuejs.org/v2/guide/')">Vue.js</button>
        </div>
      </div>
    </main>
  </div>
</template>

<script>
import SystemInformation from './LandingPage/SystemInformation';
import _ from '../../../node_modules/lodash';

export default {
  name: 'landing-page',
  components: {
    SystemInformation,
  },
  computed: {
    results: () => {
      const lists = [1, 2, 3, 4];
      return _.map(lists, item => item * item);
    },
  },
  methods: {
    open(link) {
      this.$electron.shell.openExternal(link);
    },
  },
};
</script>

<style>
@import url('https://fonts.googleapis.com/css?family=Source+Sans+Pro');
* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

body {
  font-family: 'Source Sans Pro', sans-serif;
}

#wrapper {
  background: radial-gradient(
    ellipse at top left,
    rgba(255, 255, 255, 1) 40%,
    rgba(229, 229, 229, 0.9) 100%
  );
  height: 100vh;
  padding: 60px 80px;
  width: 100vw;
}

#logo {
  height: auto;
  margin-bottom: 20px;
  width: 420px;
}

main {
  display: flex;
  justify-content: space-between;
}

main > div {
  flex-basis: 50%;
}

.left-side {
  display: flex;
  flex-direction: column;
}

.welcome {
  color: #555;
  font-size: 23px;
  margin-bottom: 10px;
}

.title {
  color: #318291;
  font-size: 20px;
  font-weight: bold;
  margin-bottom: 6px;
}

.title.alt {
  font-size: 20px;
  margin-bottom: 10px;
}

.doc p {
  color: rgb(66, 33, 33);
  margin-bottom: 10px;
}

.doc button {
  font-size: 0.8em;
  cursor: pointer;
  outline: none;
  padding: 0.75em 2em;
  border-radius: 2em;
  display: inline-block;
  color: #fff;
  background-color: #169e61;
  transition: all 0.15s ease;
  box-sizing: border-box;
  border: 1px solid #52a17e;
}

.doc button.alt {
  color: #7fdb41;
  background-color: transparent;
}

.example {
  color: #fff;
  margin: 3px;
  padding: 2px;
  width: 55.5px;
  height: 55.5px;
  display: inline-block;
  outline: 0;
  border: 1px;
  text-decoration: none;
  background: #2196f3;
  text-align: center;
  border-radius: 15%;
  box-shadow: 0 2px 5px 0 rgba(0, 0, 0, 0.16), 0 2px 10px 0 rgba(0, 0, 0, 0.12);
}
.example:hover {
  background: #42a5f5;
}
.example div {
  font-size: 1.2em;
  padding: 0;
  margin: 0.22em 0 0 0;
}
</style>
