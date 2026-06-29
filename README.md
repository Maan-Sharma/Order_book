# HFT Order Book Engine 🚀

A high-performance, professional-grade **Order Book** implementation in C++ — built for low-latency trading systems and HFT applications.

---

## Features

- **Dual-sided Order Book** — Bids sorted descending, Asks sorted ascending
- **Order Matching Engine** — Automatically matches buy and sell orders at crossed prices
- **Order Types**
  - `GoodTillCancel` — stays in the book until manually cancelled
  - `FillAndKill` — executes immediately or gets cancelled
- **Order Lifecycle Management** — Add, Cancel, Modify orders with O(log n) performance
- **Trade Reporting** — Every match generates a structured `Trade` record with bid/ask details
- **Level Info Aggregation** — Full order book depth with price and quantity at each level
- **Memory Safe** — Uses `std::shared_ptr` throughout, no raw pointer leaks

---

## Tech Stack

| Component | Technology |
|-----------|-----------|
| Language | C++17 |
| Build System | CMake |
| Data Structures | `std::map`, `std::unordered_map`, `std::list` |
| Memory Management | `std::shared_ptr` |
| Platform | Linux / Windows (MSYS2 UCRT64) |

---

## Project Structure

```
HFT_Trading_Simulation/
├── CMakeLists.txt
├── README.md
└── src/
    └── main.cpp        # Order book engine + matching logic
```

---

## Core Architecture

```
OrderBook
├── Bids (map<Price, OrderPointers> — descending)
├── Asks (map<Price, OrderPointers> — ascending)
└── Orders (unordered_map<OrderId, OrderEntry> — O(1) lookup)

Order
├── OrderType (GoodTillCancel / FillAndKill)
├── Side (Buy / Sell)
├── Price, Quantity, OrderId
└── Fill() — partial/full fill support

MatchOrders()
├── Matches best bid vs best ask
├── Generates Trade records
└── Cancels unfilled FillAndKill orders
```

---

## Getting Started

### Prerequisites
- C++17 compiler (GCC / MSVC)
- CMake 3.10+

### Build

```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
./orderbook
```

### Expected Output

```
2       # 2 orders in book (Buy @ 100, Sell @ 90) — matched!
1       # After cancelling order 1
```

---

## How It Works

### 1. Adding an Order
```cpp
orderBook.AddOrder(std::make_shared<Order>(
    OrderType::GoodTillCancel,
    orderId,
    Side::Buy,
    100,    // price
    10      // quantity
));
```

### 2. Matching Logic
When a new order is added, the engine checks if bid price >= ask price. If yes, orders are matched and a `Trade` is generated:

```
Buy  @ 100, qty 10
Sell @ 90,  qty 5
→ Trade executes at qty 5, remaining Buy qty = 5
```

### 3. Cancelling an Order
```cpp
orderBook.CancelOrder(orderId);
```
Removes the order from the book and cleans up empty price levels.

### 4. Modifying an Order
```cpp
orderBook.ModifyOrder(OrderModify(orderId, Side::Buy, 105, 20));
```
Cancels the existing order and re-adds with new parameters.

---

## Performance Characteristics

| Operation | Time Complexity |
|-----------|----------------|
| Add Order | O(log n) |
| Cancel Order | O(1) |
| Modify Order | O(log n) |
| Match Orders | O(n) per match cycle |
| Order Lookup | O(1) average |

---

## Roadmap

- [ ] Market Orders (no price limit)
- [ ] Stop Loss Orders
- [ ] Multithreaded order processing
- [ ] WebSocket market data feed
- [ ] Benchmarking suite (orders/second)
- [ ] Python bindings for backtesting integration

---

## Author

**Man Mohan Sharma**  
Quant Developer | C++ Systems | HFT & Algorithmic Trading  
[GitHub](https://github.com/yourusername) • [LinkedIn](https://linkedin.com/in/man-mohan-sharma-1aa72920a)

---

## License

MIT License — free to use and modify.
