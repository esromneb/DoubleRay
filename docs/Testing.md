# Testing

test_png.cpp is responsible for output testing.  Effectivly a full system test.

We render output and save them to disk using losless png.

# Commands


Build output classified as "test".  Compare against official output
* `make test_png && ./test_png -s scenes/hit_order_1.json`
* `make test_png && ./test_png -c -s scenes/hit_order_1.json`


# Verify Testing
Copy `hit_order_2.json` to `hit_order_1.json`, and run the commands above
