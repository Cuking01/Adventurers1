#pragma once

template<typename T>
struct Trigger;

template<typename T>
using Trigger_SA=Mem::Allocator<DS::Map_Node<u2,T>>;
template<typename T>
using Trigger_A=Mem::Pool<DS::Map_Node<u2,T>,32>;


