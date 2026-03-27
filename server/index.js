const express = require("express");
const app = express();
const PORT = 3000;
const path = require("path");
const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");

app.set("views", path.join(__dirname, "/views"));
app.set("view engine", "ejs");

app.use(express.static("public"));

const port = new SerialPort({
  path: "COM5",
  baudRate: 9600,
});

port.on("open", () => {
  console.log("Port Opened");
  port.write("Hello World form JS! \n", (err) => {
    if (err) {
      return console.log("ERROR :", err.message);
    } else {
      console.log("File Written");
    }
  });
});

const parser = port.pipe(
  new ReadlineParser({
    delimiter: "\n",
  }),
);

let data = {};

parser.on("data", (sensDat) => {
  try {
    data = JSON.parse(sensDat);
  } catch (e) {
    console.log("Error :", e);
  }
});

app.get("/", (req, res) => {
  res.render("home", { data: data });
});

app.listen(PORT, () => {
  console.log("LISTENING . . .");
});
