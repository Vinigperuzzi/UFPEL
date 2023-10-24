var createError = require('http-errors');
var express = require('express');
const cors = require('cors');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const db = require("./models")

var loginRouter = require('./routes/login');
var registerRouter = require('./routes/user');
var eventsRouter = require('./routes/events');
var userRouter = require('./routes/user');
var ratingRouter = require('./routes/ratings');
var participateRouter = require('./routes/participate');

var app = express();

// view engine setup
// app.set('views', path.join(__dirname, 'views'));
// app.set('view engine', 'pug');

app.use(cors({
  origin: 'http://localhost:5173', // Substitua pela origem apropriada
  methods: 'GET,HEAD,PUT,PATCH,POST,DELETE',
  credentials: true, // Se você estiver usando cookies ou autenticação
}));

//form
app.use(express.urlencoded({ extended: true }))

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
// app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter);
app.use('/register', registerRouter);
app.use('/events', eventsRouter);
app.use('/user', userRouter);
app.use('/ratings', ratingRouter);
app.use('/participate', participateRouter);


// catch 404 and forward to error handler
app.use(function(req, res, next) {
  //next(createError(404));
  next(res.status(404).json({error: "Route not found."}));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});


module.exports = app;

